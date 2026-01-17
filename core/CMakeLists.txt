cmake_minimum_required(VERSION 3.25)

project(core_lib VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup(REQUIRES 6.7)

# file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
# file(GLOB_RECURSE SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

set(HEADER_FILES
    include/models/processes_model.h
    include/system_info/system_info.h
    include/system_info/process_info.h
    include/system_info/windows/system_info_windows.h
    include/workers/processes_worker.h
    include/workers/controller.h
    include/workers/cpu_load_worker.h
    include/workers/memory_used_worker.h
    include/workers/worker_base.h
)

set(SOURCE_FILE
    source/models/processes_model.cpp
    source/system_info/system_info.cpp
    source/system_info/windows/system_info_windows.cpp
    source/workers/processes_worker.cpp
    source/workers/cpu_load_worker.cpp
    source/workers/memory_used_worker.cpp
    source/workers/worker_base.cpp
)   

qt_add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILE})
add_library(monitor::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}
)

# Link the target with Qt libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
)

if(ENABLE_TEST)
    add_subdirectory(tests)
endif()