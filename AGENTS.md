# Repository Guidelines

## Project Structure & Module Organization

**Pathfinder Circus** uses Godot 4.7.2, C++17, and the GL Compatibility renderer. Domain structures live in `src/domain/`; native UI and registration live in `src/app/`. `scenes/main.tscn` instantiates `CircusApp`, which builds the menu controls at runtime. `Circus rules.pdf` is the rules reference. Tests live in `tests/`; architecture and requirements are documented in `docs/`.

Targets are Windows x86_64 and Android ARM64 tablets. See `docs/development-plan.md` for milestones. Keep art/audio under `assets/` as added. Generated `.godot/`, `build/`, and `bin/` contents are ignored. Preserve stable IDs and the distinction between built-in rules and GM-created traits.

## Build, Test, and Development Commands

Run from the repository root. See `README.md` for prerequisites and explicit executable paths.

- `python tools/bootstrap.py` installs pinned build dependencies locally.
- `python tools/build.py` builds the Windows extension; `--platform android` builds ARM64 after Android bootstrap.
- `godot --editor --path .` opens the project; `godot --path .` runs it.
- `python tools/test.py` compiles and runs domain tests; `--godot <console-executable>` also runs the native-menu smoke test.
- `python tools/bootstrap.py --android --templates` prepares Android tools and export templates.
- `python tools/export.py --godot <editor-executable>` creates Windows and Android debug packages.

Restart Godot after rebuilding the native library; hot reload is disabled. Export scripts use an isolated editor configuration. Prefer the Godot UI for routine project settings.

## Coding Style & Naming Conventions

Use UTF-8 as required by `.editorconfig` and LF line endings as specified by `.gitattributes`. Use C++17, four-space indentation, `PascalCase` types and enumerators, and `snake_case` functions, fields, and files. Keep domain calculations independent of Godot UI classes. No formatter or linter is configured.

## Testing Guidelines

Domain tests use explicit checks with strict compiler warnings; no external framework or coverage threshold is configured. Name them `tests/*_test.cpp`. Run calculation tests for domain changes. For UI changes, run `tests/menu_smoke.gd` and inspect rendered layouts with `tests/menu_capture.gd`. GDScript is used only for test harnesses. Validate device behavior on Android; a successful APK export alone is not a device test.

## Commit & Pull Request Guidelines

No Git history is available in this checkout, so existing commit conventions cannot be established. Use short, imperative commit subjects, such as `Add circus encounter scene`. Keep commits focused. Pull requests should explain the change, link relevant issues, describe validation, and include screenshots or recordings for visual changes. Do not commit generated `.godot/` data.
