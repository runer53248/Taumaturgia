add_executable(main_build_into_t_${addons}
    main_build_into_t.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_scheme_${addons}
    main_scheme.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_create_ordered_property_list_${addons}
    main_create_ordered_property_list.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_mix_give_properties_${addons}
    main_mix_give_properties.cpp
)

add_executable(main_have_properties_${addons}
    main_have_properties.cpp
)

add_executable(main_improve_properties_${addons}
    main_improve_properties.cpp
)
