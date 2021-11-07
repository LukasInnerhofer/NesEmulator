cmake_minimum_required(VERSION 3.13.4)

project(libnes)

add_library(${PROJECT_NAME}
    source/cpu_memory.cpp
    source/mapper.cpp
    source/nes.cpp
    source/nrom.cpp
    source/ricoh_2c02.cpp
    include/${PROJECT_NAME}/cartridge.h
    include/${PROJECT_NAME}/cpu_memory.h
    include/${PROJECT_NAME}/mapper.h
    include/${PROJECT_NAME}/nes.h
    include/${PROJECT_NAME}/nrom.h
    include/${PROJECT_NAME}/ricoh_2c02.h
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

get_target_property(LIBMOS6502_INCLUDE libmos6502 INCLUDE_DIRECTORIES)
get_target_property(LIBMOS6502_DEFINITIONS libmos6502 COMPILE_DEFINITIONS)
get_target_property(LIBUTILITIES_INCLUDE_DIRECTORIES libutilities INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBMOS6502_INCLUDE})
if(${LIBMOS6502_DEFINITIONS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIBMOS6502_DEFINITIONS})
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBUTILITIES_INCLUDE_DIRECTORIES})

if(LOG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LIB_NES_LOG)
endif()

target_link_libraries(${PROJECT_NAME} libmos6502)
