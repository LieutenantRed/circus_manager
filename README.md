# Pathfinder Circus

A Godot/C++ companion for a GM running the circus rules on Windows and Android tablets.

The first milestone provides a main menu, a circus-naming form, and an in-memory management overview. New Circus accepts a name, initializes the C++ circus model, and displays its starting Prestige, balance, and roster counts. Back navigation preserves the current session, which can be reopened with **Return to current circus**.

**Saving is not implemented yet.** Continue is disabled, and closing the app loses the current session. Management features shown as coming soon belong to later milestones. The Android build is prepared; physical-tablet testing was deferred at the user's request.

## Run the Prepared Builds

- Windows: extract `build/exports/PathfinderCircus-windows-debug.zip`, then run `PathfinderCircus.exe`. Keep the accompanying `.pck` and `.dll` beside it.
- Android: install `build/exports/android/PathfinderCircus.apk` on an ARM64 tablet running Android 7.0 or later. This is a locally debug-signed test build.

These generated artifacts are ignored by version control. Use the instructions below to reproduce them.

## Build from Source on Windows

Prerequisites: Python 3 with pip, Godot **4.7.2**, and a MinGW-w64 C++ compiler. The scripts look for the compiler at `C:\msys64\mingw64\bin`; pass `--compiler-dir` to use another location. Gameplay and UI behavior are C++; the GDScript files under `tests/` are test harnesses only.

```powershell
python tools/bootstrap.py
python tools/build.py
godot --editor --path .
```

Substitute your Godot executable path if `godot` is not on `PATH`. Restart an already-open Godot editor after rebuilding the native extension, then run the main scene. Native hot reload is disabled for this milestone.

The bootstrap script installs SCons 4.10.1 locally and downloads checksum-verified godot-cpp 10.0.0-stable. The bindings target API 4.7. Dependencies and generated files stay under ignored `build/` and `bin/` directories. `.gdignore` prevents Godot from scanning build tools and dependency projects.

## Android and Packaging

```powershell
python tools/bootstrap.py --android --templates
python tools/build.py --platform android
python tools/export.py --godot "D:\path\Godot_v4.7.2-stable_win64.exe"
```

Build the Windows extension first as above; the editor needs it while exporting. The export script produces both debug packages. Use `--platform windows` or `--platform android` for a single target.

The optional bootstrap downloads roughly 2.3 GB of archives, including export templates, NDK 28.1.13356709, Android Build Tools 36.0.0, Platform Tools 37.0.1, and Temurin JDK 17.0.16+8. More space is needed after extraction. This setup uses Godot's standard APK export, without Gradle.

Export uses a self-contained editor copy under `build/editor/` with project-local SDK settings, leaving your installed editor's settings alone. A conventional Android debug keystore is generated under `build/`; it is for testing, not store publication. Third-party archives retain their license files.

Native outputs:

- `bin/circus.windows.template_debug.x86_64.dll`
- `bin/libcircus.android.template_debug.arm64.so`

Package outputs:

- `build/exports/windows/PathfinderCircus.exe` and accompanying data/library files
- `build/exports/PathfinderCircus-windows-debug.zip`
- `build/exports/android/PathfinderCircus.apk`

The export helper generates debug builds. Release signing and distribution are later milestones.

## Validation

```powershell
python tools/test.py
python tools/test.py --godot "D:\path\Godot_v4.7.2-stable_win64_console.exe"
```

The first command builds/runs strict-warning domain tests. The second also exercises the real native menu scene: mouse input, name validation, Unicode, creation, Escape/Back navigation, session replacement, and responsive layouts. Build/import the extension before running the menu test.

To capture the rendered menu, form, and overview for visual inspection:

```powershell
godot --path . --script res://tests/menu_capture.gd
```

Images are written to `build/`. This briefly opens a window. Desktop rendering has been checked in landscape and portrait. Tablet follow-up should verify tapping, the on-screen keyboard, Back behavior, and orientation changes. Suspending/closing the app does not yet guarantee preservation of an in-memory session.

## Project Layout

- `src/domain/`: engine-independent circus structures and rules.
- `src/app/`: native Godot class, menu navigation, and model integration.
- `scenes/main.tscn`: main scene; `CircusApp` constructs its controls at runtime.
- `circus.gdextension`: platform-specific native library paths.
- `tools/`: dependency, build, export, and test entry points.
- `docs/`: [development plan](docs/development-plan.md), [design decisions](docs/design-notes.md), and rules documentation.

Build references: [official godot-cpp bindings](https://github.com/godotengine/godot-cpp/tree/10.0.0-stable) and [Godot Android export documentation](https://docs.godotengine.org/en/stable/tutorials/export/exporting_for_android.html).
