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

add_executable(main_token
    main_token.cpp
)

add_executable(main_pipe0
    Pipe/main_pipe0.cpp
)
add_executable(main_pipe1-1
    Pipe/main_pipe1-1.cpp
)
add_executable(main_pipe1-2
    Pipe/main_pipe1-2.cpp
)
add_executable(main_pipe2
    Pipe/main_pipe2.cpp
)
add_executable(main_pipe3
    Pipe/main_pipe3.cpp
)
add_executable(main_pipe4
    Pipe/main_pipe4.cpp
)

add_executable(main_ignore_order_Ap_${addons}
    main_ignore_order.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_ignore_order_Ap_${addons} PUBLIC WITH_ADD_PROPERTIES)
