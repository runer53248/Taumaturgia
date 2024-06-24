add_executable(main_simple_${addons}
    main_simple.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_fix_${addons}
    main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
add_executable(main_fix_Ap_${addons}
    main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_fix_Ap_${addons} PUBLIC WITH_ADD_PROPERTIES)
