add_subdirectory(AttackStrategyTest)
add_subdirectory(AccessTraitsTest)

add_executable(${PROJECT_NAME}-test
    main_tests.cpp
    ../../Object/Object.cpp
)