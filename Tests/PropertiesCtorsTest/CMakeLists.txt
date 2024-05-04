add_executable(PropertiesCtorsTest_${addons}
PropertiesCtorsTest.cpp)
target_link_libraries(PropertiesCtorsTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME PropertiesCtorsTest COMMAND PropertiesCtorsTest_${addons} --gtest_color=yes)
