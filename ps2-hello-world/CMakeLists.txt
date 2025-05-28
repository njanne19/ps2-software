cmake_minimum_required(VERSION 3.0) 
project(hello-ps2 C) 

# Tell CMake to use the PS2 toolchain file: 
# We assume PS2SDK and PS2DEV are exported in the shell 
set(CMAKE_TOOLCHAIN_FILE "${PS2SDK}/ps2dev.cmake" CACHE STRING "")

# Define our executable, pointing to the source file:
add_executable(hello.elf src/hello.c)