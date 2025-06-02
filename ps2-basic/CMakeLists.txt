cmake_minimum_required(VERSION 3.0) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ps2-basic C) 

# Tell CMake to use the PS2 toolchain file: 
# We assume PS2SDK and PS2DEV are exported in the shell 
set(CMAKE_TOOLCHAIN_FILE "${PS2SDK}/ps2dev.cmake" CACHE STRING "")

# Define our executable, pointing to the source file:
# option(BUILD_FOR_IOP "Compile the IOP version instead of EE" OFF)
add_executable(basic.elf 
   src/main.c
)

target_include_directories(
   basic.elf
   PRIVATE
   ${PS2DEV}/gskit/include
   ${PS2DEV}/dmakit/include
   ${PS2SDK}/ee/include
   ${PS2SDK}/common/include
)

target_link_libraries(basic.elf
   gskit
   gskit_toolkit
   dmakit
   draw
   math3d
)