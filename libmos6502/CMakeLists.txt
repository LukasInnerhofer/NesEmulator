cmake_minimum_required(VERSION 3.13.4)

project(libmos6502)

add_library(${PROJECT_NAME}
    source/mos6502.cpp
    include/${PROJECT_NAME}/mos6502.h
    include/${PROJECT_NAME}/memory.h)

target_include_directories(${PROJECT_NAME} PUBLIC include)

if(LOG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIBMOS6502_LOG)
endif()
