# Building Replay Buffer Pro plugin on Windows

## 1. Prerequisites

- Windows 10/11 64-bit / Linux 64-bit (MacOS are not supported at this time, PRs welcome!)
- Visual Studio 2022+ with "Desktop development with C++"
- CMake 3.16+ from https://cmake.org/download/

## 2. Build OBS Studio

```bash
# Clone OBS (with submodules)
git clone --recursive https://github.com/obsproject/obs-studio.git
cd obs-studio

# Configure with Visual Studio 2022
# On Windows OBS will download remaining dependencies automatically
cmake -B build -G "Visual Studio 17 2022" -A x64

# Build OBS (RelWithDebInfo to match plugin build)
cmake --build build --config RelWithDebInfo

# [Optional] Install into custom directory for testing
# (or system-wide if you don't specify --prefix; requires elevated shell).
cmake --install build --config RelWithDebInfo --prefix <install-path>
```

## 3. Build Plugin

```bash
git clone https://github.com/joshuapotter/replay-buffer-pro.git
cd replay-buffer-pro

# Configure with matching compiler and architecture
# Dependencies used in OBS build will be reused automatically
cmake -B build -G "Visual Studio 17 2022" -A x64

# Build the plugin (RelWithDebInfo to match OBS)
cmake --build build --config RelWithDebInfo

# Install into custom directory (same used for OBS install)
cmake --install build --config RelWithDebInfo --prefix <obs-install-path>
```

**Note:** Ensure the `obs-studio` repository is located as a sibling of this plugin (same parent directory),
or override it during configuration with `-DOBS_ROOT_DIR=<path-to-obs-studio>`.
You may need to run the install command elevated (Run as administrator) to install to Program Files.
