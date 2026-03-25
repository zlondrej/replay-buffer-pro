FROM ubuntu:noble

RUN apt-get update && apt-get install -y \
  # Build system dependencies
  build-essential \
  ccache \
  clang \
  clang-format \
  cmake \
  curl \
  extra-cmake-modules \
  git \
  ninja-build \
  pkg-config \
  zsh \
  # OBS Core dependencies
  libavcodec-dev \
  libavdevice-dev \
  libavfilter-dev \
  libavformat-dev \
  libavutil-dev \
  libcmocka-dev \
  libcurl4-openssl-dev \
  libgl1-mesa-dev \
  libgles2-mesa-dev \
  libglvnd-dev \
  libjansson-dev \
  libluajit-5.1-dev \
  libmbedtls-dev \
  libpci-dev \
  libpipewire-0.3-dev \
  libqrcodegencpp-dev \
  librist-dev \
  libsimde-dev \
  libsrt-openssl-dev \
  libswresample-dev \
  libswscale-dev \
  libwayland-dev \
  libx11-dev \
  libx11-xcb-dev \
  libx264-dev \
  libxcb-composite0-dev \
  libxcb-randr0-dev \
  libxcb-shm0-dev \
  libxcb-xfixes0-dev \
  libxcb-xinerama0-dev \
  libxcb1-dev \
  libxcomposite-dev \
  libxinerama-dev \
  libxss-dev \
  python3-dev \
  swig \
  uthash-dev \
  # OBS Qt6 dependencies
  qt6-base-dev \
  qt6-base-private-dev \
  qt6-svg-dev \
  qt6-wayland \
  qt6-image-formats-plugins \
  # Plugin dependencies
  libasio-dev \
  libasound2-dev \
  libdrm-dev \
  libfdk-aac-dev \
  libfontconfig-dev \
  libfreetype6-dev \
  libjack-jackd2-dev \
  libpulse-dev libsndio-dev \
  libspeexdsp-dev \
  libudev-dev \
  libv4l-dev \
  libva-dev \
  libvlc-dev \
  libvpl-dev \
  libwebsocketpp-dev \
  nlohmann-json3-dev \
  && rm -rf /var/lib/apt/lists/*

ARG UID=1000
ARG GID=1000

# Create a non-root user to run the build process.
# Remove the default 'ubuntu' user to avoid UID/GID conflicts.
RUN userdel ubuntu \
  && groupadd --gid "$GID" builder \
  && useradd --create-home --shell /bin/bash --uid "$UID" --gid "$GID" builder

USER builder
WORKDIR /home/builder