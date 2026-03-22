# Utilities and Shared Infrastructure

This document covers shared utilities used across the plugin.

## OBS data RAII
- `OBSDataRAII` wraps `obs_data_t` and releases it in the destructor.
- It is a simple ownership wrapper used by settings and hotkey persistence.
- Copying is disabled to avoid double-free; move semantics are not implemented.

## Logging
- `Logger` provides `info`, `warning`, and `error` helpers.
- Each helper writes to OBS logs using `blog(...)` with the `[ReplayBufferPro]` prefix.
- Buffer size is fixed to 4096 chars per log call.

## Duration formatting
- `duration-format` formats localized duration labels (seconds/minutes/hours).
- Used for save button labels and hotkey descriptions.

## Related code
- `src/utils/obs-utils.hpp`
- `src/utils/obs-utils.cpp`
- `src/utils/duration-format.hpp`
- `src/utils/duration-format.cpp`
- `src/utils/logger.hpp`
