"""Compile/run domain tests and optionally run the Godot native-menu smoke test."""
import argparse
import os
import shutil
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--compiler-dir", default=r"C:\msys64\mingw64\bin")
parser.add_argument("--godot", type=Path, help="Godot console executable; native extension must already be built/imported")
args = parser.parse_args()
env = os.environ.copy()
if Path(args.compiler_dir).is_dir():
    env["PATH"] = args.compiler_dir + os.pathsep + env.get("PATH", "")
(ROOT / "build").mkdir(exist_ok=True)
test_exe = ROOT / "build/circus_tests.exe"
sources = sorted((ROOT / "src/domain").glob("*.cpp")) + sorted((ROOT / "tests").glob("*_test.cpp"))
compiler = shutil.which("g++", path=env["PATH"])
if compiler is None:
    parser.error("g++ was not found; supply --compiler-dir")
subprocess.run([compiler, "-std=c++17", "-Wall", "-Wextra", "-Wpedantic", "-Werror", "-Isrc",
                *map(str, sources), "-o", str(test_exe)], cwd=ROOT, env=env, check=True)
subprocess.run([str(test_exe)], cwd=ROOT, env=env, check=True)
if args.godot:
    subprocess.run([str(args.godot.resolve()), "--headless", "--path", str(ROOT),
                    "--script", "res://tests/menu_smoke.gd", "--log-file",
                    str(ROOT / "build/menu-smoke.log")], cwd=ROOT, env=env, check=True)
