add_executable(AddPropertyTest_${addons}
AddPropertyTest.cpp)
target_link_libraries(AddPropertyTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME AddPropertyTest_${addons} COMMAND AddPropertyTest_${addons} --gtest_color=yes)
