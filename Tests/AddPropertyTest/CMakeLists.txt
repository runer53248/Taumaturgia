add_executable(AddPropertyTest_${addons}
AddPropertyTest.cpp)
target_link_libraries(AddPropertyTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME AddPropertyTest_${addons} COMMAND AddPropertyTest_${addons} --gtest_color=yes)

add_executable(PipeTest_${addons}
PipeTest.cpp)
target_link_libraries(PipeTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME PipeTest_${addons} COMMAND PipeTest_${addons} --gtest_color=yes)
