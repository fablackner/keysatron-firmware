#ifndef TUSB_CONFIG_H_
#define TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUSB_MCU                OPT_MCU_STM32F4
#define CFG_TUSB_OS                 OPT_OS_NONE
#define CFG_TUSB_DEBUG              0

// Board Port Mapping:
// Port 0: STM32 USB_OTG_FS (PA11/PA12, J2, USB_IN) -> HOST
// Port 1: STM32 USB_OTG_HS embedded FS PHY (PB14/PB15, J3, USB_PC) -> DEVICE
#define BOARD_TUH_RHPORT            0
#define BOARD_TUH_MAX_SPEED         OPT_MODE_FULL_SPEED

#define BOARD_TUD_RHPORT            1
#define BOARD_TUD_MAX_SPEED         OPT_MODE_FULL_SPEED

//--------------------------------------------------------------------
// HOST CONFIGURATION (Port 0 - Keyboard IN)
//--------------------------------------------------------------------
#define CFG_TUH_ENABLED             1
#define CFG_TUH_MAX_SPEED           BOARD_TUH_MAX_SPEED
#define CFG_TUH_ENUMERATION_BUFSIZE 256
#define CFG_TUH_HUB                 1
#define CFG_TUH_DEVICE_MAX          (CFG_TUH_HUB ? 4 : 1)
#define CFG_TUH_HID                 4
#define CFG_TUH_HID_EPIN_BUFSIZE    64
#define CFG_TUH_HID_EPOUT_BUFSIZE   64
#define CFG_TUH_MEM_ALIGN           __attribute__ ((aligned(4)))
#define CFG_TUH_MEM_SECTION

//--------------------------------------------------------------------
// DEVICE CONFIGURATION (Port 1 - PC OUT)
//--------------------------------------------------------------------
#define CFG_TUD_ENABLED             1
#define CFG_TUD_MAX_SPEED           BOARD_TUD_MAX_SPEED
#define CFG_TUD_ENDPOINT0_SIZE      64
#define CFG_TUD_HID                 1
#define CFG_TUD_HID_EP_BUFSIZE      64
#define CFG_TUD_MEM_ALIGN           __attribute__ ((aligned(4)))
#define CFG_TUD_MEM_SECTION

#ifdef __cplusplus
}
#endif

#endif // TUSB_CONFIG_H_
