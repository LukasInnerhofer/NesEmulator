cmake_minimum_required(VERSION 3.13.4)

set(LIB_NAME lib_nes)

project(${LIB_NAME})

add_library(${LIB_NAME}
    source/cpu_memory.cpp
    source/mapper.cpp
    source/nes.cpp
    source/nrom.cpp
    source/ricoh_2c02.cpp
    include/${LIB_NAME}/cartridge.h
    include/${LIB_NAME}/cpu_memory.h
    include/${LIB_NAME}/mapper.h
    include/${LIB_NAME}/nes.h
    include/${LIB_NAME}/nrom.h
    include/${LIB_NAME}/ricoh_2c02.h
)

target_include_directories(${LIB_NAME} PUBLIC include)

get_target_property(LIB_MOS6502_INCLUDE lib_mos6502 INCLUDE_DIRECTORIES)
get_target_property(LIB_MOS6502_DEFINITIONS lib_mos6502 COMPILE_DEFINITIONS)
target_include_directories(${LIB_NAME} PRIVATE ${LIB_MOS6502_INCLUDE})
target_compile_definitions(${LIB_NAME} PRIVATE ${LIB_MOS6502_DEFINITIONS})

if(LOG)
    target_compile_definitions(${LIB_NAME} PUBLIC LIB_NES_LOG)
endif()

target_link_libraries(${LIB_NAME} lib_mos6502)
