add_executable(${PROJECT_NAME}-main_build_into_t
    main_build_into_t.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_scheme
    main_scheme.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(${PROJECT_NAME}-main_create_ordered_property_list
    main_create_ordered_property_list.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
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
