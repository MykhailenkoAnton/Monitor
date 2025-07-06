cmake_minimum_required(VERSION 3.25)
project(Monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_TEST "Enable testing functionality" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(gui_monitor_desktop)
add_subdirectory(core)