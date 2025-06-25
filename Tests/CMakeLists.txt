add_subdirectory(AttackStrategyTest)
add_subdirectory(AccessTraitsTest)
add_subdirectory(PropertiesCtorsTest)

add_subdirectory(AddPropertyTest)

add_executable(test_${addons}
    main_tests.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)