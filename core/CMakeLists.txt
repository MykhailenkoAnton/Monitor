cmake_minimum_required(VERSION 3.25)

project(core_lib VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup(REQUIRES 6.7)

# file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
# file(GLOB_RECURSE SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

set(HEADER_FILES

)

set(SOURCE_FILE
    source/
)   

qt_add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILE})
add_library(monitor::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(ENABLE_TEST)
    add_subdirectory(tests)
endif()