cmake_minimum_required(VERSION 3.13.4)

project(libmos6502)

add_library(${PROJECT_NAME}
    source/mos6502.cpp
    include/${PROJECT_NAME}/mos6502.h
    include/${PROJECT_NAME}/memory.h)

target_include_directories(${PROJECT_NAME} PUBLIC include)

get_target_property(LIBUTILITIES_INCLUDE_DIRECTORIES libutilities INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUTILITIES_INCLUDE_DIRECTORIES})

if(LOG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIBMOS6502_LOG)
endif()
