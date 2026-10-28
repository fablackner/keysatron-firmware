#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board_keysatron.h"
#include "layout_engine.h"
#include "usb_descriptors.h"
#include "tusb.h"

// Active host keyboard instance
static uint8_t host_dev_addr = 0;
static uint8_t host_instance = 0;
static bool host_keyboard_mounted = false;

// HID Report Transmission Buffer
typedef struct {
  uint8_t modifier;
  uint8_t keys[6];
  bool pending;
} keyboard_report_buffer_t;

static keyboard_report_buffer_t pending_report = {0};

static void send_keyboard_report(uint8_t modifier, const uint8_t keys[6]) {
  if (tud_hid_ready()) {
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keys);
    pending_report.pending = false;
  } else {
    // Save report to send immediately when endpoint becomes ready
    pending_report.modifier = modifier;
    if (keys) {
      memcpy(pending_report.keys, keys, 6);
    } else {
      memset(pending_report.keys, 0, 6);
    }
    pending_report.pending = true;
  }
}

// LED Blink Pattern State
static uint32_t blink_prev_ms = 0;
static uint32_t mode_blink_remaining = 0;
static uint32_t mode_blink_prev_ms = 0;

static void trigger_activation_indication(bool active) {
  mode_blink_remaining = active ? 4 : 2; // 2 fast blinks for active, 1 long blink for stopped
  board_led_write(true);
  mode_blink_prev_ms = board_millis();
}

static void led_task(void) {
  uint32_t now = board_millis();

  if (mode_blink_remaining > 0) {
    if (now - mode_blink_prev_ms >= 120) {
      mode_blink_prev_ms = now;
      mode_blink_remaining--;
      board_led_toggle();
    }
    return;
  }

  // Normal heartbeat: 1000ms when famak is active, 250ms when waiting for keyboard, 2000ms when stopped
  uint32_t interval = 1000;
  if (!host_keyboard_mounted) {
    interval = 250;
  } else if (!layout_is_active()) {
    interval = 2000;
  }

  if (now - blink_prev_ms >= interval) {
    blink_prev_ms = now;
    board_led_toggle();
  }
}

int main(void) {
  // Initialize hardware, clocks (168MHz), GPIOs, NVIC
  board_init();

  // Initialize keyboard layout remapping engine
  layout_engine_init();

  // Initialize Host stack on Port 0 (USB_IN, PA11/PA12)
  const tusb_rhport_init_t host_init = {
    .role = TUSB_ROLE_HOST,
    .speed = TUSB_SPEED_FULL
  };
  tusb_init(BOARD_TUH_RHPORT, &host_init);

  // Initialize Device stack on Port 1 (USB_PC, PB14/PB15)
  const tusb_rhport_init_t dev_init = {
    .role = TUSB_ROLE_DEVICE,
    .speed = TUSB_SPEED_FULL
  };
  tusb_init(BOARD_TUD_RHPORT, &dev_init);

  // Initial LED feedback: 2 fast blinks
  for (int i = 0; i < 4; i++) {
    board_led_toggle();
    board_delay_ms(80);
  }

  while (1) {
    // TinyUSB Host task
    tuh_task();

    // TinyUSB Device task
    tud_task();

    // Flush pending report if endpoint became ready
    if (pending_report.pending && tud_hid_ready()) {
      tud_hid_keyboard_report(REPORT_ID_KEYBOARD, pending_report.modifier, pending_report.keys);
      pending_report.pending = false;
    }

    // Status LED handler
    led_task();
  }

  return 0;
}

//--------------------------------------------------------------------+
// TinyUSB Host Callbacks (Port 0 - USB_IN Keyboard)
//--------------------------------------------------------------------+

// Invoked when device with HID interface is mounted
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
  (void) desc_report;
  (void) desc_len;

  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
    host_dev_addr = dev_addr;
    host_instance = instance;
    host_keyboard_mounted = true;

    // Start listening for reports from keyboard
    tuh_hid_receive_report(dev_addr, instance);
  }
}

// Invoked when device with HID interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
  if (dev_addr == host_dev_addr && instance == host_instance) {
    host_keyboard_mounted = false;
    host_dev_addr = 0;
    host_instance = 0;

    // Send empty report to PC so no stuck keys remain
    uint8_t empty_keys[6] = {0};
    send_keyboard_report(0, empty_keys);
  }
}

// Invoked when received report from keyboard
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD && len >= 8) {
    hid_keyboard_report_t const* in_report = (hid_keyboard_report_t const*) report;

    uint8_t out_modifier = 0;
    uint8_t out_keys[6] = {0};

    // Process German ISO to Famak (4 layers: Normal, Sym, Nav, Exo)
    bool state_changed = layout_process_report(in_report->modifier, in_report->keycode,
                                               &out_modifier, out_keys);

    if (state_changed) {
      trigger_activation_indication(layout_is_active());
    }

    // Toggle onboard LED on every key event received from keyboard
    board_led_toggle();

    // Forward translated report to PC via buffered transmission
    send_keyboard_report(out_modifier, out_keys);
  }

  // Request next report from keyboard
  tuh_hid_receive_report(dev_addr, instance);
}

// Invoked when a report transfer from keyboard failed (re-arm polling)
void tuh_hid_report_failed_cb(uint8_t dev_addr, uint8_t instance, xfer_result_t result) {
  (void) result;
  tuh_hid_receive_report(dev_addr, instance);
}

//--------------------------------------------------------------------+
// TinyUSB Device Callbacks (Port 1 - USB_PC)
//--------------------------------------------------------------------+

// Invoked when sent report successfully to PC
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len) {
  (void) instance;
  (void) report;
  (void) len;

  if (pending_report.pending && tud_hid_ready()) {
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, pending_report.modifier, pending_report.keys);
    pending_report.pending = false;
  }
}

// Invoked when received GET_REPORT control request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;
  return 0;
}

// Invoked when received SET_REPORT control request (e.g. Host PC changes CapsLock / NumLock LED)
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
  (void) instance;
  (void) report_id;

  if (report_type == HID_REPORT_TYPE_OUTPUT && bufsize >= 1) {
    uint8_t led_status = buffer[0];

    // Forward LED state to physical keyboard if connected
    if (host_keyboard_mounted) {
      tuh_hid_set_report(host_dev_addr, host_instance, 0, HID_REPORT_TYPE_OUTPUT, &led_status, 1);
    }
  }
}
