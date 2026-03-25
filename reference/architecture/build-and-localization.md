# Build, Packaging, and Localization

This document describes how the plugin is built, packaged, and localized.

## Build system (CMake)
- Project name: `replay-buffer-pro`.
- C++ standard: C++17.
- Sources: module entry, plugin, managers, UI, and utilities.
- Links against OBS, Qt6 (Widgets/Core), and FFmpeg libraries.

### Windows build
- Assumes an OBS Studio checkout adjacent to this repo (`../obs-studio`).
- Reuses `CMAKE_PREFIX_PATH` from the OBS build cache when available.
- Links against `obs.lib` and `obs-frontend-api.lib`.

### Non-Windows build
- Uses `find_package(libobs REQUIRED)`.
- Can use `OBS_INSTALL_DIR` to help discovery of installed OBS packages.

## Install and packaging
- Installs plugin binary into OBS plugin directory and data files into OBS data path.
- `prepare_release` builds a release directory structure and zips it.

## Localization
- Default locale is `en-US`.
- Localization keys live in `data/locale/en-US.ini` under `[ReplayBufferPro]`.
- UI text is accessed via `obs_module_text(...)`.

## Related code
- `CMakeLists.txt`
- `data/locale/en-US.ini`
