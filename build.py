import os
import subprocess
import sys

# Configuration
source_dir = os.path.abspath(".")
build_dir = os.path.abspath("out/build/Debug")
generator = "Ninja"
build_type = "Debug"

# Step 1: Configure
os.makedirs(build_dir, exist_ok=True)
subprocess.check_call([
    "cmake",
    f"-S{source_dir}",
    f"-B{build_dir}",
    f"-G{generator}",
    f"-DCMAKE_BUILD_TYPE={build_type}"
])

# Step 2: Build
subprocess.check_call([
    "cmake",
    "--build", build_dir
])
