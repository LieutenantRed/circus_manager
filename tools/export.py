"""Export debug builds using a project-local copy of the Godot 4.7.2 editor."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys
import zipfile

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build"


def package_windows(directory):
    archive = directory.parent / "PathfinderCircus-windows-debug.zip"
    with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as output:
        for path in sorted(directory.rglob("*")):
            if path.is_file():
                output.write(path, path.relative_to(directory))
    print("Packaged " + str(archive), flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--godot", required=True, type=Path, help="Path to the Godot 4.7.2 Windows editor .exe")
    parser.add_argument("--platform", choices=["windows", "android", "all"], default="all")
    args = parser.parse_args()
    original = args.godot.resolve()
    if not original.is_file():
        parser.error("Godot executable does not exist")
    editor_dir = BUILD / "editor"
    editor_dir.mkdir(parents=True, exist_ok=True)
    editor = editor_dir / original.name
    if not editor.exists() or editor.stat().st_mtime < original.stat().st_mtime:
        shutil.copy2(original, editor)
    console = original.with_name(original.stem + "_console.exe")
    if console.exists():
        shutil.copy2(console, editor_dir / console.name)
        executable = editor_dir / console.name
    else:
        executable = editor
    (editor_dir / "_sc_").touch()
    settings_dir = editor_dir / "editor_data"
    settings_dir.mkdir(exist_ok=True)
    env = os.environ.copy()
    settings = '[gd_resource type="EditorSettings" format=3]\n\n[resource]\n'
    if args.platform in ("android", "all"):
        java = BUILD / "jdk"
        sdk = BUILD / "android"
        if not (java / "bin/keytool.exe").exists() or not (sdk / "platform-tools/adb.exe").exists():
            parser.error("Run python tools/bootstrap.py --android --templates first")
        env["JAVA_HOME"] = str(java)
        env["ANDROID_HOME"] = str(sdk)
        keystore = BUILD / "debug.keystore"
        if not keystore.exists():
            subprocess.run([str(java / "bin/keytool.exe"), "-genkeypair", "-keystore", str(keystore),
                            "-storepass", "android", "-alias", "androiddebugkey", "-keypass", "android",
                            "-keyalg", "RSA", "-keysize", "2048", "-validity", "10000",
                            "-dname", "CN=Android Debug,O=Android,C=US"], check=True, env=env)
        for key, value in {"java_sdk_path": java.as_posix(), "android_sdk_path": sdk.as_posix(),
                           "debug_keystore": keystore.as_posix(), "debug_keystore_user": "androiddebugkey",
                           "debug_keystore_pass": "android"}.items():
            settings += f'export/android/{key} = "{value}"\n'
    (settings_dir / "editor_settings-4.7.tres").write_text(settings, encoding="utf-8")
    common = [str(executable), "--headless", "--path", str(ROOT)]
    subprocess.run(common + ["--editor", "--quit", "--log-file", str(BUILD / "export-import.log")], check=True, env=env)
    targets = [("windows", "Windows Desktop", "PathfinderCircus.exe"), ("android", "Android", "PathfinderCircus.apk")]
    for platform, preset, filename in targets:
        if args.platform not in (platform, "all"):
            continue
        destination = BUILD / "exports" / platform / filename
        destination.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(common + ["--export-debug", preset, str(destination), "--log-file",
                                 str(BUILD / f"export-{platform}.log")], check=True, env=env)
        if not destination.exists():
            raise RuntimeError("Export did not create " + str(destination))
        print("Exported " + str(destination), flush=True)
        if platform == "windows":
            package_windows(destination.parent)


if __name__ == "__main__":
    main()
