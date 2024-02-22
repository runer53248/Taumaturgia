add_executable(AttackStrategyTest-1
    ${PROJECT_SOURCE_DIR}/Object/Object.cpp
    ../mainTest.cpp
    AttackStrategyTest.cpp)
target_link_libraries(AttackStrategyTest-1 PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME AttackStrategyTest-1 COMMAND AttackStrategyTest-1 --gtest_color=yes)

add_executable(AttackStrategyTest-2
    ${PROJECT_SOURCE_DIR}/Object/Object.cpp
    ../mainTest.cpp
    AttackStrategyTest.cpp)
target_link_libraries(AttackStrategyTest-2 PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME AttackStrategyTest-2 COMMAND AttackStrategyTest-2 --gtest_color=yes)

target_compile_definitions(AttackStrategyTest-1 PUBLIC)
target_compile_definitions(AttackStrategyTest-2 PUBLIC WITH_ADD_PROPERTIES)