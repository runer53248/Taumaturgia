# add_executable(main_simple_1_${addons}
#     main_simple_1.cpp
#     ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
# )

# add_executable(main_simple_1_${addons}_Ap
#     main_simple_1.cpp
#     ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
# )
# target_compile_definitions(main_simple_1_${addons}_Ap PUBLIC WITH_ADD_PROPERTIES)

add_executable(main_simple_${addons}
    main_simple.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
