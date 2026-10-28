FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

# Install build toolchain, ARM cross-compiler with newlib, and flashing utilities
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    openocd \
    stlink-tools \
    usbutils \
    git \
    udev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["make"]
