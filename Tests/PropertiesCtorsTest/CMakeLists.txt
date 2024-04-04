add_executable(PropertiesCtorsTest
PropertiesCtorsTest.cpp)
target_link_libraries(PropertiesCtorsTest PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME PropertiesCtorsTest COMMAND PropertiesCtorsTest --gtest_color=yes)
