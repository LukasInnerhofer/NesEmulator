cmake_minimum_required(VERSION 3.13.4)

set(LIB_NAME LibNes)

add_library(${LIB_NAME}
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

target_include_directories(${LIB_NAME} PUBLIC include)

get_target_property(LIB_MOS6502_INCLUDE LibMos6502 INCLUDE_DIRECTORIES)
get_target_property(LIB_MOS6502_DEFINITIONS LibMos6502 COMPILE_DEFINITIONS)
target_include_directories(${LIB_NAME} PRIVATE ${LIB_MOS6502_INCLUDE})
target_compile_definitions(${LIB_NAME} PRIVATE ${LIB_MOS6502_DEFINITIONS})

if(LOG)
    target_compile_definitions(${LIB_NAME} PUBLIC LIB_NES_LOG)
endif()

target_link_libraries(${LIB_NAME} LibMos6502)
