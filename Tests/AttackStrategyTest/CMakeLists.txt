add_executable(AttackStrategyTest_${addons}
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
    AttackStrategyTest.cpp)
target_link_libraries(AttackStrategyTest_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME AttackStrategyTest_${addons} COMMAND AttackStrategyTest_${addons} --gtest_color=yes)

target_compile_definitions(AttackStrategyTest_${addons} PUBLIC)
