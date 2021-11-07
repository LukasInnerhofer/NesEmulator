cmake_minimum_required(VERSION 3.13.4)

project(nes_emulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    ${PROJECT_NAME} 
    source/main.cpp
    source/screen_libgraphics.h
    source/screen_libgraphics.cpp)

set(INSTALL_PATH bin/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${INSTALL_PATH})

add_subdirectory(libutilities)
add_subdirectory(libmos6502)
add_subdirectory(libnes)
set(LIBGRAPHICS_INSTALL_PATH ${INSTALL_PATH})
add_subdirectory(libgraphics)

get_target_property(LIBMOS6502_INCLUDE_DIRECTORIES libmos6502 INCLUDE_DIRECTORIES)
get_target_property(LIBMOS6502_DEFINITIONS libmos6502 COMPILE_DEFINITIONS)
get_target_property(LIBNES_INCLUDE_DIRECTORIES libnes INCLUDE_DIRECTORIES)
get_target_property(LIBNES_DEFINITIONS libnes COMPILE_DEFINITIONS)
get_target_property(LIBGRAPHICS_INCLUDE_DIRECTORIES libgraphics INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBMOS6502_INCLUDE_DIRECTORIES})
if(${LIBMOS6502_DEFINITIONS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIBMOS6502_DEFINITIONS})
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBNES_INCLUDE_DIRECTORIES})
if(${LIBNES_DEFINITIONS})
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIBNES_DEFINITIONS})
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBGRAPHICS_INCLUDE_DIRECTORIES})

if(LOG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NES_EMULATOR_LOG)
endif()

target_link_libraries(${PROJECT_NAME} libnes)
target_link_libraries(${PROJECT_NAME} libgraphics)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} pthread GL X11)
endif()

option(LOG "Enable logging to file" OFF)