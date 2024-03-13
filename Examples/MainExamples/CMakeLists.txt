add_subdirectory(add_property_examples)
add_subdirectory(helpers_examples)

add_executable(${PROJECT_NAME}-main_ignore_and_tuple
    main_ignore_and_tuple.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_Property
    main_Property.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_introduction
    main_introduction.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_user_property
    main_user_property.cpp
)

add_executable(${PROJECT_NAME}-main_user_property2
    main_user_property_2.cpp
)

add_executable(${PROJECT_NAME}-main_user_property3
    main_user_property_3.cpp
)
add_executable(${PROJECT_NAME}-main_user_property3-aware
    main_user_property_3.cpp
)
target_compile_definitions(${PROJECT_NAME}-main_user_property3-aware 
    PUBLIC USER_PROPERTY_SELF_AWARE
)
