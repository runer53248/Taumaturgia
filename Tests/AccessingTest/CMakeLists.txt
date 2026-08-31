add_executable(accessing_properties_tests_${addons}
    accessing_properties_tests.cpp)
target_link_libraries(accessing_properties_tests_${addons} PRIVATE 
    GTest::GTest GTest::Main "-lstdc++exp")
add_test(NAME accessing_properties_tests_${addons} COMMAND accessing_properties_tests_${addons} --gtest_color=yes)

add_executable(accessing_properties_tests_additional_${addons}
    additional_tests.cpp)
target_link_libraries(accessing_properties_tests_additional_${addons} PRIVATE 
    GTest::GTest GTest::Main "-lstdc++exp")
add_test(NAME accessing_properties_tests_additional_${addons} COMMAND accessing_properties_tests_additional_${addons} --gtest_color=yes)

