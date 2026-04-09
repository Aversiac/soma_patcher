import os
import subprocess

source_dir = os.path.abspath(".")
build_dir = os.path.abspath("out/build/Debug")
generator = "Visual Studio 17 2022"
build_type = "Debug"

os.makedirs(build_dir, exist_ok=True)

subprocess.check_call([
    "cmake",
    f"-S{source_dir}",
    f"-B{build_dir}",
    f"-G{generator}",
    "-A", "x64"
])

subprocess.check_call([
    "cmake",
    "--build", build_dir,
    "--config", build_type
])  