cmake_minimum_required(VERSION 3.13.4)

add_executable(${PROJECT_NAME} source/main.cpp)

get_target_property(LIB_MOS6502_INCLUDE LibMos6502 INCLUDE_DIRECTORIES)
get_target_property(LIB_MOS6502_DEFINITIONS LibMos6502 COMPILE_DEFINITIONS)
get_target_property(LIB_NES_INCLUDE LibNes INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_MOS6502_INCLUDE})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIB_MOS6502_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_NES_INCLUDE})

target_link_libraries(${PROJECT_NAME} LibNes)
