cmake_minimum_required(VERSION 3.13.4)

set(LIB_NAME lib_mos6502)

project(${LIB_NAME})

add_library(${LIB_NAME}
    source/mos6502.cpp
    include/${LIB_NAME}/mos6502.h
    include/${LIB_NAME}/memory.h)

target_include_directories(${LIB_NAME} PUBLIC include)

if(LOG)
    target_compile_definitions(${LIB_NAME} PUBLIC LIB_MOS6502_LOG)
endif()
