add_executable(main_simple_${addons}
    main_simple.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_fix_${addons}
    Fix/main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
add_executable(main_fix_Ap_${addons}
    Fix/main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_fix_Ap_${addons} PUBLIC WITH_ADD_PROPERTIES)

add_executable(main_fix_noOrder_${addons}
    Fix/main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_fix_noOrder_${addons} PUBLIC IGNORE_ORDER_LIST)
add_executable(main_fix_noOrder_Ap_${addons}
    Fix/main_fix.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_fix_noOrder_Ap_${addons} PUBLIC IGNORE_ORDER_LIST WITH_ADD_PROPERTIES)

add_executable(main_token_${addons}
    main_token.cpp
)

add_subdirectory(Pipe)

add_executable(main_ignore_order_${addons}
    main_ignore_order.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
