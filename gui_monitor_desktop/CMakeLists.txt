cmake_minimum_required(VERSION 3.25)

project(gui_monitor_desktop VERSION 0.1 LANGUAGES CXX)
set(APP_NAME app_${PROJECT_NAME})

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt6Charts)
qt_standard_project_setup(REQUIRES 6.7)

qt_add_executable(${APP_NAME}
    main.cpp

    mainwindow.cpp
    mainwindow.h
    Widgets/process_view_wdget.h
    Widgets/process_view_wdget.cpp
    Widgets/system_info_widgets.h
    Widgets/system_info_widgets.cpp
    Widgets/system_info_widget.h
    Widgets/system_info_widget.cpp
    Widgets/cpu_widget.h
    Widgets/cpu_widget.cpp
    Widgets/memory_widget.h
    Widgets/memory_widget.cpp
)

target_include_directories(${APP_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${APP_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Charts
    monitor::core_lib
)