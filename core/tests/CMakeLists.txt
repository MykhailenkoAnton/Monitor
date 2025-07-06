enable_testing()
find_package(Qt6 REQUIRED COMPONENTS Test)

set(ITEMS
    tst_mytest.cpp
    tst_mytest2.cpp
)

foreach(file ${ITEMS})

    get_filename_component(test_name ${file} NAME_WE)

    add_executable(${test_name} ${file})
    add_test(NAME ${test_name} COMMAND ${test_name})
    target_link_libraries(${test_name} PRIVATE Qt6::Test monitor::core_lib)

    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR})

endforeach()
