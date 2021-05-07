cmake_minimum_required(VERSION 3.13.4)

set(LIB_NAME LibMos6502)

add_library(${LIB_NAME}
    source/mos6502.cpp
    include/mos6502.h
    include/mos6502_memory.h)

target_include_directories(${LIB_NAME} PUBLIC include)
