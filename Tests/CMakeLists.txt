add_subdirectory(AttackStrategyTest)
add_subdirectory(AccessTraitsTest)
add_subdirectory(PropertiesCtorsTest)

add_executable(${PROJECT_NAME}-test
    main_tests.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)