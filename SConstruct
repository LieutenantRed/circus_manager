#!/usr/bin/env python
import os

bindings = "build/deps/godot-cpp-10.0.0-stable"
if not os.path.isfile(bindings + "/SConstruct"):
    raise RuntimeError("Run python tools/bootstrap.py first.")
env = SConscript(bindings + "/SConstruct", {"api_version": "4.7"})
env.Append(CPPPATH=["src"])
if env.get("is_msvc", False):
    env.Append(CXXFLAGS=["/std:c++17", "/EHsc"])
else:
    env.Append(CXXFLAGS=["-std=c++17", "-fexceptions"])
if env["platform"] == "windows" and env.get("use_mingw", False):
    env.Append(LINKFLAGS=["-static-libgcc", "-static-libstdc++"])
sources = Glob("src/domain/*.cpp") + Glob("src/app/*.cpp")
basename = "libcircus" if env["platform"] == "android" else "circus"
library = env.SharedLibrary("bin/" + basename + env["suffix"] + env["SHLIBSUFFIX"], source=sources)
Default(library)
