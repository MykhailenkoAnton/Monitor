cmake_minimum_required(VERSION 3.25)
project(Monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_TEST "Enable testing functionality" ON)

add_subdirectory(gui_monitor_desktop)
add_subdirectory(core)