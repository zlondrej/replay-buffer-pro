# Replay Buffer Flow (Save with Duration Limiting)

This document explains how the plugin saves replay buffer content with optional duration limiting.

## Responsibilities
- Trigger replay buffer saves through OBS frontend APIs.

## Save segment flow
1. User clicks a duration button or hotkey.
2. `ReplayBufferManager::saveSegment(duration, parent)` validates:
   - Replay buffer is active.
   - `duration <= currentBufferLength` from `SettingsManager`.
3. If valid, the method calls `obs_frontend_replay_buffer_save_duration(duration)` — a new OBS frontend API.
4. The replay buffer segment is saved, with packets past the replay duration filtered out.

## Save full buffer flow
1. User clicks “Save Replay Buffer”.
2. `ReplayBufferManager::saveFullBuffer(...)` checks buffer activity.
3. If active, it calls `obs_frontend_replay_buffer_save()` (standard OBS API, no duration limiting).
4. The entire current replay buffer is saved without filtering.

## Trimming details
- Packets past the replay durations are filtered during muxing by OBS ffmpeg plugin.

## Error handling
- UI warnings show when the replay buffer is inactive or the requested duration exceeds buffer length.

## Key classes and functions
- `ReplayBufferManager::saveSegment(...)` — calls `obs_frontend_replay_buffer_save_duration()` API
- `ReplayBufferManager::saveFullBuffer(...)` — calls `obs_frontend_replay_buffer_save()` API

## Related code
- `src/managers/replay-buffer-manager.hpp`
- `src/managers/replay-buffer-manager.cpp`