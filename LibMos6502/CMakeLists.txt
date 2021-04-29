cmake_minimum_required(VERSION 3.20.1)

add_library(LibMos6502 
    source/mos6502.cpp
    include/mos6502.h
    include/mos6502_memory.h)

target_include_directories(LibMos6502 PUBLIC include)