add_executable(main2_${addons}
    main2.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main3-1_${addons}
    main3.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main3-2_${addons}
    main3.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main3-3_${addons}
    main3.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main3-4_${addons}
    main3.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

target_compile_definitions(main3-1_${addons} PUBLIC)
target_compile_definitions(main3-2_${addons} PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main3-3_${addons} PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main3-4_${addons} PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(main4-1_${addons}
    main4.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main4-2_${addons}
    main4.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main4-3_${addons}
    main4.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main4-4_${addons}
    main4.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

target_compile_definitions(main4-1_${addons} PUBLIC)
target_compile_definitions(main4-2_${addons} PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main4-3_${addons} PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main4-4_${addons} PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(main5-1_${addons}
    main5.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main5-2_${addons}
    main5.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main5-3_${addons}
    main5.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main5-4_${addons}
    main5.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

target_compile_definitions(main5-1_${addons} PUBLIC)
target_compile_definitions(main5-2_${addons} PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main5-3_${addons} PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main5-4_${addons} PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)