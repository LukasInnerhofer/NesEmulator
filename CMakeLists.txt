cmake_minimum_required(VERSION 3.13.4)

project(nes_emulator)

option(LOG "Enable logging to file" OFF)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib_mos6502)
add_subdirectory(lib_nes)
add_subdirectory(nes_emulator)
