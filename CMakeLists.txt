cmake_minimum_required(VERSION 3.13.4)

project(NesEmulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(LibMos6502)
add_subdirectory(LibNes)
add_subdirectory(NesEmulator)
