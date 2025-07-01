add_executable(accessing_properties_tests_${addons}
    accessing_properties_tests.cpp)
target_link_libraries(accessing_properties_tests_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME accessing_properties_tests_${addons} COMMAND accessing_properties_tests_${addons} --gtest_color=yes)
target_compile_definitions(accessing_properties_tests_${addons} PUBLIC)
