"""Download pinned build dependencies into build/ (Windows host, Python 3)."""
import argparse
import hashlib
from pathlib import Path
import shutil
import subprocess
import sys
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / "build"


def fetch(name, url, checksum, algorithm="sha256"):
    downloads = BUILD / "downloads"
    downloads.mkdir(parents=True, exist_ok=True)
    target = downloads / name
    if not target.exists():
        print("Downloading " + name, flush=True)
        partial = target.with_suffix(target.suffix + ".partial")
        with urllib.request.urlopen(url, timeout=60) as response, partial.open("wb") as output:
            shutil.copyfileobj(response, output, 1024 * 1024)
        partial.replace(target)
    digest = hashlib.new(algorithm)
    with target.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
    if digest.hexdigest() != checksum:
        raise RuntimeError(f"Checksum mismatch: {target}; remove this cached archive and retry.")
    return target


def unpack(archive, destination, strip_root=False, only=None):
    destination.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(archive) as source:
        for info in source.infolist():
            if info.is_dir():
                continue
            parts = Path(info.filename).parts
            relative = Path(*parts[1:]) if strip_root else Path(*parts)
            if only is not None and relative.name not in only:
                continue
            target = (destination / relative).resolve()
            if not target.is_relative_to(destination.resolve()):
                raise RuntimeError("Unsafe archive path")
            target.parent.mkdir(parents=True, exist_ok=True)
            with source.open(info) as data, target.open("wb") as output:
                shutil.copyfileobj(data, output)
    print("Ready: " + str(destination.relative_to(ROOT)), flush=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--templates", action="store_true", help="Get Godot 4.7.2 Windows/Android export templates (~1.3 GB archive)")
    parser.add_argument("--android", action="store_true", help="Get the Windows-host Android toolchain and JDK (~1 GB)")
    args = parser.parse_args()
    BUILD.mkdir(exist_ok=True)
    (BUILD / ".gdignore").touch()
    if not (BUILD / "python/SCons").exists():
        subprocess.run([sys.executable, "-m", "pip", "install", "--disable-pip-version-check",
                        "--target", str(BUILD / "python"), "scons==4.10.1"], check=True)
    archive = fetch("godot-cpp-10.0.0.zip",
                    "https://github.com/godotengine/godot-cpp/archive/refs/tags/10.0.0-stable.zip",
                    "c763a08b8ec18dae300cd54bb8848faf1a5fd11da629449d16649a72a1884727")
    if not (BUILD / "deps/godot-cpp-10.0.0-stable/SConstruct").exists():
        unpack(archive, BUILD / "deps")
    if args.templates and not (BUILD / "templates/android_debug.apk").exists():
        archive = fetch("Godot_v4.7.2-stable_export_templates.tpz",
                        "https://github.com/godotengine/godot-builds/releases/download/4.7.2-stable/Godot_v4.7.2-stable_export_templates.tpz",
                        "f298490b8d44d934be425a5a65a51bf15f422428b229a06a6e11d9ffea248011")
        unpack(archive, BUILD / "templates", strip_root=True,
               only={"windows_debug_x86_64.exe", "windows_release_x86_64.exe", "android_debug.apk", "android_release.apk", "version.txt"})
    if args.android:
        packages = [
            ("android-ndk-r28b-windows.zip", "c7d82072807fcabbd6ee356476761d8729307185", "android/ndk/28.1.13356709", "source.properties"),
            ("build-tools_r36_windows.zip", "f16ccffd34de8790dede813a6c7d8e2c11a27b50", "android/build-tools/36.0.0", "apksigner.bat"),
            ("platform-tools_r37.0.1-win.zip", "e03e78b1d80b396f1c3358e31251cb31740e1110", "android/platform-tools", "adb.exe"),
        ]
        for name, checksum, folder, marker in packages:
            destination = BUILD / folder
            if not (destination / marker).exists():
                archive = fetch(name, "https://dl.google.com/android/repository/" + name, checksum, "sha1")
                unpack(archive, destination, strip_root=True)
        if not (BUILD / "jdk/bin/java.exe").exists():
            archive = fetch("OpenJDK17U-jdk_x64_windows_hotspot_17.0.16_8.zip",
                            "https://github.com/adoptium/temurin17-binaries/releases/download/jdk-17.0.16%2B8/OpenJDK17U-jdk_x64_windows_hotspot_17.0.16_8.zip",
                            "8c7cfff78a55c56ebaf470ed6a89c6466b47d8274bdabdda997d7507c20325c5")
            unpack(archive, BUILD / "jdk", strip_root=True)
    print("Bootstrap complete.", flush=True)


if __name__ == "__main__":
    main()
