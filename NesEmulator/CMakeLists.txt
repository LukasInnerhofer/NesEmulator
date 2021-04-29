cmake_minimum_required(VERSION 3.20.1)

add_executable(NesEmulator source/main.cpp)

target_link_libraries(NesEmulator LibMos6502 LibNes)

get_target_property(LIB_MOS6502_INCLUDE LibMos6502 INCLUDE_DIRECTORIES)
get_target_property(LIB_NES_INCLUDE LibNes INCLUDE_DIRECTORIES)
target_include_directories(NesEmulator PRIVATE ${LIB_MOS6502_INCLUDE})
target_include_directories(NesEmulator PRIVATE ${LIB_NES_INCLUDE})