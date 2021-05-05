cmake_minimum_required(VERSION 3.18.5)

add_library(LibNes 
    source/cpu_memory.cpp 
    source/mapper.cpp 
    source/nes.cpp 
    source/nrom.cpp
    include/cartridge.h
    include/cpu_memory.h
    include/mapper.h
    include/nes.h
    include/nrom.h
    include/ppu.h
)

target_include_directories(LibNes PUBLIC include)

get_target_property(LIB_MOS6502_INCLUDE LibMos6502 INCLUDE_DIRECTORIES)
target_include_directories(LibNes PRIVATE ${LIB_MOS6502_INCLUDE})
