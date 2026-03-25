# Replay Buffer Pro

[![GitHub Release](https://img.shields.io/github/v/release/joshuapotter/replay-buffer-pro)
![GitHub Release Date](https://img.shields.io/github/release-date/joshuapotter/replay-buffer-pro?display_date=published_at)](https://github.com/JoshuaPotter/replay-buffer-pro/releases/latest/download/replay-buffer-pro-windows-x64.zip)

This OBS Studio plugin expands upon the built-in Replay Buffer, allowing users to save recent footage at different lengths with customizable save buttons, similar to how PlayStation/Xbox's "Save Recent Gameplay" functionality.

**Note:** This plugin is 64-bit only, as it requires OBS Studio 29.0.0+ which dropped 32-bit support. The plugin uses Qt6 which also only provides 64-bit builds for Windows.

## How It Works
OBS keeps a rolling buffer of the last few seconds or minutes of footage in memory using the built-in replay buffer. The length of this footage is defined in settings. If the amount of footage exceeds the length in settings, old footage is overwritten as new footage is recorded.

Unlike the default Replay Buffer, which saves a fixed duration, this OBS Studio plugin allows users to save different lengths on demand. Set the replay buffer length, then clip custom lengths of footage automatically. Example: Set your replay buffer to 10 minutes. Save the last 30 seconds, 2 minutes, or 5 minutes instantly with UI buttons or hotkeys.

The project website is currently hosted via GitHub Pages.

![Plugin UI](./plugin_ui.png)

## Usage

### Saving Clips
1. Start the Replay Buffer in OBS
2. Click any save clip button (customizable durations) or use the assigned hotkey
3. Use the Customize button to set your preferred clip lengths

   ![Customize UI](./customize_ui.png)

4. The plugin will:
   - Save the full replay buffer
   - Automatically trim to the selected duration (Without re-encoding)
   - Replace the original file with the trimmed version

### Buffer Length
- Quickly adjust built-in replay buffer length (1s to 6h) without digging through the settings

### Hotkeys
- Assign hotkeys to each save duration button in OBS Settings > Hotkeys

## Installation

### From Release

1. Download latest release
2. Extract and merge the folder `obs-studio` with your OBS Studio installation

Final file structure should look like this:
```
obs-studio/
├── obs-plugins/
│   └── 64bit/
│       └── replay-buffer-pro.dll
└── data/
    └── obs-plugins/
        └── replay-buffer-pro/
            └── locale/
                └── en-US.ini
```

### From Source

See below for instructions to build from source.

After building, you can use the command to automatically copy the files or manually copy the compiled files:
1. Copy compiled plugin:
   - `replay-buffer-pro.dll` → `C:/Program Files/obs-studio/obs-plugins/64bit/`
2. Copy from source `data` directory:
   - Data files → `C:/Program Files/obs-studio/data/obs-plugins/replay-buffer-pro/`

Note: Close OBS before installing or copying the DLL. You may need administrator privileges to copy files to Program Files.

## Building from Source

Requires OBS Studio 30.0.0+ (64-bit) built from source.

### Building on Windows

Please follow the instructions on [how to build the plugin on Windows](./README/build-windows.md).

### Building on Linux

Please follow the instructions on [how to build the plugin on Linux](./README/build-linux.md).

### Building on MacOS

MacOS builds are not documented/supported. PRs welcome.

### Releasing the Plugin
Iterate the version in `CMakeLists.txt`, then run:
```bash
cmake -B build
cmake --build build --config RelWithDebInfo --target prepare_release
```

### Project Structure

```
obs-studio/              # OBS Studio source code (see build instructions)
replay-buffer-pro/
├── CMakeLists.txt       # Build configuration
├── data/
│   └── locale/          # Translations
├── src/                 # Source files
│   ├── managers/        # Core functionality managers
│   ├── plugin/          # Main plugin implementation
│   ├── ui/              # User interface components
│   └── utils/           # Utility classes (including video-trimmer)
├── docs/                # Project website source
├── reference/           # Developer documentation
└── README.md
```

## Troubleshooting

- Verify plugin DLL location
- Check OBS logs for errors
- For trimming issues:
  - Check disk space
  - Check write permissions in output directory
- When building from source
  - Ensure correct location and setup of OBS build
  - Run install command in a terminal with admin privileges

## Third-Party Software

This plugin uses OBS Studio's built-in FFmpeg libraries (libavformat) for video trimming functionality. FFmpeg is licensed under the LGPL v2.1+ license.

## License

GPL v2 or later. See LICENSE file for details.
