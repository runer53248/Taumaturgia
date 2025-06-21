add_subdirectory(add_property_examples)
add_subdirectory(helpers_examples)

add_executable(constructors_${addons}
    main_constructors.cpp
)

add_executable(main_ignore_and_tuple_${addons}
    main_ignore_and_tuple.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_plain_properties_${addons}
    main_plain_properties.cpp
)

add_executable(main_Property_priority_${addons}
    main_Property_priority.cpp
)

add_executable(main_introduction_${addons}
    main_introduction.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_user_property_${addons}
    main_user_property.cpp
)

add_executable(main_user_property2_${addons}
    main_user_property_2.cpp
)

add_executable(main_user_property3_${addons}
    main_user_property_3.cpp
)

add_executable(main_constexpr_traits_${addons}
    main_constexpr_traits.cpp
)

add_executable(main_project_advancing_${addons}
    main_project_advancing.cpp)
