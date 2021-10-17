cmake_minimum_required(VERSION 3.13.4)

add_executable(${PROJECT_NAME} source/main.cpp)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM "linux")
endif()

get_target_property(LIB_MOS6502_INCLUDE lib_mos6502 INCLUDE_DIRECTORIES)
get_target_property(LIB_MOS6502_DEFINITIONS lib_mos6502 COMPILE_DEFINITIONS)
get_target_property(LIB_NES_INCLUDE lib_nes INCLUDE_DIRECTORIES)
get_target_property(LIB_NES_DEFINITIONS lib_nes COMPILE_DEFINITIONS)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_MOS6502_INCLUDE})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIB_MOS6502_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_NES_INCLUDE})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIB_NES_DEFINITIONS})

if(LOG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NES_EMULATOR_LOG)
endif()

target_link_libraries(${PROJECT_NAME} lib_nes)

if(${PLATFORM} STREQUAL "linux")
    target_link_libraries(${PROJECT_NAME} pthread)
endif()
