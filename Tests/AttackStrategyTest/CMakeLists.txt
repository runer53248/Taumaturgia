add_executable(AttackStrategyTest-1_${addons}
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
    AttackStrategyTest.cpp)
target_link_libraries(AttackStrategyTest-1_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME AttackStrategyTest-1 COMMAND AttackStrategyTest-1 --gtest_color=yes)

add_executable(AttackStrategyTest-2_${addons}
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
    AttackStrategyTest.cpp)
target_link_libraries(AttackStrategyTest-2_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME AttackStrategyTest-2 COMMAND AttackStrategyTest-2 --gtest_color=yes)

target_compile_definitions(AttackStrategyTest-1_${addons} PUBLIC)
target_compile_definitions(AttackStrategyTest-2_${addons} PUBLIC WITH_ADD_PROPERTIES)