cmake_minimum_required(VERSION 3.16)
project(soma_patcher LANGUAGES CXX)

# ──────────────────────────────────────────────────────────────
# Compiler
# ────────────────────────────────────────────────────────────── ALT + 196
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ──────────────────────────────────────────────────────────────
# Target + Sources
# ──────────────────────────────────────────────────────────────
file(GLOB_RECURSE PATCHER_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(SomaPatcher_Test ${PATCHER_SRC})
add_executable(SomaPatcher ${PATCHER_SRC})

target_include_directories(SomaPatcher PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)
target_include_directories(SomaPatcher_Test PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_compile_definitions(SomaPatcher PRIVATE OVERWRITE_EXES)
