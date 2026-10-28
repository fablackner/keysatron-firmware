#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_NAME="keysatron-dev"

# Ensure image exists
if ! docker image inspect "$IMAGE_NAME" >/dev/null 2>&1; then
    echo "==> Building Docker image '$IMAGE_NAME'..."
    docker build -t "$IMAGE_NAME" "$DIR"
fi

ACTION="${1:-build}"

case "$ACTION" in
    build)
        echo "==> Building Keysatron firmware inside container..."
        docker run --rm -v "$DIR":/workspace "$IMAGE_NAME" make
        ;;
    clean)
        echo "==> Cleaning build artifacts inside container..."
        docker run --rm -v "$DIR":/workspace "$IMAGE_NAME" make clean
        ;;
    flash)
        echo "==> Flashing firmware to STM32F405 via ST-LINK inside container..."
        docker run --rm --privileged \
            -v /dev/bus/usb:/dev/bus/usb \
            -v "$DIR":/workspace \
            "$IMAGE_NAME" \
            openocd -f openocd.cfg -c "init; reset halt; program build/keysatron-firmware.bin verify reset exit 0x08000000"
        ;;
    shell)
        echo "==> Starting interactive container shell..."
        docker run -it --rm --privileged \
            -v /dev/bus/usb:/dev/bus/usb \
            -v "$DIR":/workspace \
            "$IMAGE_NAME" /bin/bash
        ;;
    *)
        echo "Usage: $0 [build|clean|flash|shell]"
        exit 1
        ;;
esac
