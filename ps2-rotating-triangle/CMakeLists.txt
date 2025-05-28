cmake_minimum_required(VERSION 3.0) 
project(ps2-triangle-demo C) 

# Tell CMake to use the PS2 toolchain file: 
# We assume PS2SDK and PS2DEV are exported in the shell 
set(CMAKE_TOOLCHAIN_FILE "${PS2SDK}/ps2dev.cmake" CACHE STRING "")

# Define our executable, pointing to the source file:
add_executable(rotating_triangle.elf src/main.c)

target_link_libraries(rotating_triangle.elf
   gskit
   gskit_toolkit
   dmakit
#    kernel
#    sifrpc
#    c
#    m
)