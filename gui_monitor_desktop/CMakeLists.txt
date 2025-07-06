cmake_minimum_required(VERSION 3.25)

project(gui_monitor_desktop VERSION 0.1 LANGUAGES CXX)
set(APP_NAME app_${PROJECT_NAME})

find_package(Qt6 REQUIRED COMPONENTS Qml Quick)
qt_standard_project_setup(REQUIRES 6.7)

qt_add_resources(RESOURCES
    res/resources.qrc
)

qt_add_executable(${APP_NAME}
    main.cpp
    ${RESOURCES}
)

# Add QML module
qt_add_qml_module(${APP_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    QML_FILES
        Main.qml
        ${QML_FILES}
)

target_link_libraries(${APP_NAME} PRIVATE
    Qt6::Quick
    monitor::core_lib
)