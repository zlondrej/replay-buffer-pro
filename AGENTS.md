# AGENTS

This file is a concise handoff for agents working in the Replay Buffer Pro OBS plugin.

## Project summary
- Adds a dockable OBS UI for replay buffer controls.
- Lets users adjust replay buffer length and save clips of customizable durations.
- Saves selected clip durations directly through OBS frontend replay buffer APIs.

## Architecture map (start here)
- Module entry + OBS integration: `src/main.cpp`
- Dock widget + UI orchestration: `src/plugin/plugin.hpp`, `src/plugin/plugin.cpp`
- UI components + tick labels: `src/ui/ui-components.hpp`, `src/ui/ui-components.cpp`
- Replay buffer manager: `src/managers/replay-buffer-manager.hpp`, `src/managers/replay-buffer-manager.cpp`
- Settings manager: `src/managers/settings-manager.hpp`, `src/managers/settings-manager.cpp`
- Save button settings: `src/managers/save-button-settings.hpp`, `src/managers/save-button-settings.cpp`
- Hotkey manager: `src/managers/hotkey-manager.hpp`, `src/managers/hotkey-manager.cpp`
- Utilities: `src/utils/obs-utils.*`, `src/utils/logger.hpp`, `src/utils/duration-format.*`
- Config constants: `src/config/config.hpp`
- Localization: `data/locale/en-US.ini`
- Build system: `CMakeLists.txt`

## Core runtime flows
### Buffer length update
1. Slider/spinbox/tick label changes value in the dock.
2. Debounce timer expires.
3. `SettingsManager::updateBufferLengthSettings(...)` writes `RecRBTime` into OBS profile config.
4. If a replay output exists, updates `max_time_sec` and calls `obs_output_update(...)`.

### Save segment
1. User clicks a duration button or hotkey.
2. `ReplayBufferManager::saveSegment(...)` validates buffer active and duration <= current length.
3. `obs_frontend_replay_buffer_save_duration(...)` is called with the requested duration.
4. OBS saves only the requested duration segment.

### Save full buffer
1. User clicks “Save Replay Buffer”.
2. `ReplayBufferManager::saveFullBuffer(...)` calls `obs_frontend_replay_buffer_save()`.
3. OBS saves the full replay buffer.

## Key components and ownership
- `ReplayBufferPro::Plugin` (dock) owns UI, managers, timers, and OBS event wiring.
- `UIComponents` builds the UI and manages enabled/disabled state.
- `ReplayBufferManager` handles save requests.
- `SettingsManager` reads/writes OBS profile config and updates output settings.
- `HotkeyManager` registers per-duration hotkeys and persists bindings.

## Configuration and persistence
- Buffer length config key: `RecRBTime`.
- Config section is `AdvOut` for Advanced mode, otherwise `SimpleOutput`.
- Hotkey bindings are stored in `hotkey_bindings.json` under the module config path.
- Custom save button durations are stored in `save_button_settings.json` under the module config path.

## Build and localization
- Built via CMake; links OBS and Qt6.
- Locale strings in `data/locale/en-US.ini` accessed with `obs_module_text(...)`.

## Not present
- No custom OBS sources, filters, or outputs are registered. The plugin uses OBS frontend replay buffer APIs.

## Documentation upkeep
- More documentation is available in `reference/` and README.md.
- Project website source lives in `docs/` and should be updated when relevant.
- Any changes to the project should be reflected in `reference/` for developers, `docs/` for plugin users and distribution, README.md for project introduction and setup, and this `AGENTS.md` file for agentic coding assistance.
