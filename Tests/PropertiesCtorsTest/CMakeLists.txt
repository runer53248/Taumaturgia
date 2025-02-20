add_executable(PropertiesCtorsTest_${addons}
PropertiesCtorsTest.cpp)
target_link_libraries(PropertiesCtorsTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME PropertiesCtorsTest_${addons} COMMAND PropertiesCtorsTest_${addons} --gtest_color=yes)
