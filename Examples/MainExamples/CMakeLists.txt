add_subdirectory(add_property_examples)

add_executable(${PROJECT_NAME}-main_ignore_and_tuple
    main_ignore_and_tuple.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_create_ordered_property_list
    main_create_ordered_property_list.cpp
    ../../Object/Object.cpp
)
add_executable(${PROJECT_NAME}-main_Property
    main_Property.cpp
    ../../Object/Object.cpp
)
add_executable(${PROJECT_NAME}-main_build_into_t
    main_build_into_t.cpp
    ../../Object/Object.cpp
)
add_executable(${PROJECT_NAME}-main_add_properties
    main_add_properties.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_scheme
    main_scheme.cpp
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


add_executable(${PROJECT_NAME}-main_mix_give_properties
    main_mix_give_properties.cpp
)

add_executable(${PROJECT_NAME}-main_have_properties
    main_have_properties.cpp
)

add_executable(${PROJECT_NAME}-main_improve_properties
    main_improve_properties.cpp
)

add_executable(${PROJECT_NAME}-main_improve_properties-aware
    main_improve_properties.cpp
)
target_compile_definitions(${PROJECT_NAME}-main_improve_properties-aware
    PUBLIC USER_PROPERTY_SELF_AWARE
)
