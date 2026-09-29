"""Build the native extension with the workspace-local SCons installation."""
import argparse
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--platform", choices=["windows", "android"], default="windows")
parser.add_argument("--target", choices=["template_debug", "template_release"], default="template_debug")
parser.add_argument("--compiler-dir", default=r"C:\msys64\mingw64\bin")
parser.add_argument("--jobs", type=int, default=8)
args = parser.parse_args()
env = os.environ.copy()
env["PYTHONPATH"] = str(ROOT / "build/python")
if Path(args.compiler_dir).is_dir():
    env["PATH"] = args.compiler_dir + os.pathsep + env.get("PATH", "")
command = [sys.executable, "-m", "SCons", f"platform={args.platform}", f"target={args.target}",
           "build_profile=build_profile.json", f"-j{args.jobs}"]
if args.platform == "windows":
    command += ["arch=x86_64", "use_mingw=yes"]
else:
    env["ANDROID_HOME"] = str(ROOT / "build/android")
    command += ["arch=arm64", "ndk_version=28.1.13356709"]
sys.exit(subprocess.call(command, cwd=ROOT, env=env))
