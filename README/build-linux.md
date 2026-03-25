# Building Replay Buffer Pro plugin on Linux

## 1. Prerequisites

- Linux 64-bit
- [Optional] Docker *
- Follow OBS's [Build Instructions for Linux](https://github.com/obsproject/obs-studio/wiki/build-instructions-for-linux) to install all necessary dependencies, or build inside `Ubuntu.dockerfile`.

*\* Docker build should work on majority of distributions, but it doesn't guarantee compatibility, with your system libraries.
Even running different version Ubuntu might cause the OBS build or plugin to be incompatible with your system.
For best results, you either have to create custom-fit dockerfile or install dependencies system-wide.*


## 2. Clone OBS Studio and Replay Buffer Pro repositories

```bash
# Clone OBS (with submodules)
git clone --recursive https://github.com/obsproject/obs-studio.git

# Clone Replay Buffer Pro
git clone https://github.com/joshuapotter/replay-buffer-pro.git
```

## [Optional] Checkout matching OBS Studio version

If you want to build the plugin for your system OBS installation, you have to checkout matching version.

Determine your OBS studio version:
```bash
obs --version
```

Checkout the matching version tag:
```bash
cd obs-studio

# E.g. git checkout 32.0.4
git checkout <obs-version>
```

## [Optional] Enter the docker shell

Follow this step if you want to build in isolated environment.

```bash
cd replay-buffer-pro

# Build and tag the docker image
docker build -t obs-ubuntu -f Ubuntu.dockerfile --build-arg "UID=$UID" --build-arg "GID=$GID" .

cd ..

# Enter the docker shell.
# Both directories will be mounted in home directory.
docker run -ti --rm --volume ./obs-studio:/home/builder/obs-studio --volume ./replay-buffer-pro:/home/builder/replay-buffer-pro obs-ubuntu
```

## 3. Build OBS Studio

**Note:** Some OBS plugins are disabled to reduce needed dependencies.
But, the built plugin should still work with official version of OBS provided by your distro
(if it has compatible API).

```bash
cd obs-studio

# Configure build
cmake -B build -G Ninja -DENABLE_AJA=FALSE -DENABLE_NVENC=FALSE -DENABLE_BROWSER=FALSE -DENABLE_NEW_MPEGTS_OUTPUT=FALSE -DENABLE_WEBRTC=FALSE

# Build OBS
cmake --build build

# Install into a directory for discoverability by cmake,
# (or system-wide if you don't specify --prefix; requires elevated shell).
cmake --install build --prefix build/install
```

## 3. Build Plugin

**Note:** Ensure the `obs-studio` repository is located as a sibling of this plugin (same parent directory),
or override it during configuration with `-DOBS_ROOT_DIR=<path-to-obs-studio>`.
You may need to run the install command elevated to install system-wide.

```bash
cd replay-buffer-pro

# Configure build
cmake -B build -G Ninja

# Build the plugin
cmake --build build

# Install into custom directory (same used for OBS install)
cmake --install build --prefix ../obs-studio/build/install
```