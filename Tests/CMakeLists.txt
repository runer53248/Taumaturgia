add_subdirectory(AttackStrategyTest)
add_subdirectory(AccessTraitsTest)
add_subdirectory(PropertiesCtorsTest)
add_subdirectory(AddPropertyTest)
add_subdirectory(AccessingTest)
add_subdirectory(have_get_features_Test)

add_executable(test_${addons} main_tests.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
