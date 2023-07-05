add_executable(AttackStrategyTest
    ${PROJECT_SOURCE_DIR}/Object/Object.cpp
    ../mainTest.cpp
    AttackStrategyTest.cpp)

target_link_libraries(AttackStrategyTest PRIVATE 
    -lgtest
    -lgmock)

add_test(NAME AttackStrategyTest COMMAND AttackStrategyTest --gtest_color=yes)
