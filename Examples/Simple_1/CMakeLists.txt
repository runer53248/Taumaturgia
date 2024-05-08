include_directories(${PROJECT_SOURCE_DIR})

add_executable(main_simple_1
    main_simple_1.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)

add_executable(main_simple_1_Ap
    main_simple_1.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_simple_1_Ap PUBLIC 
    WITH_ADD_PROPERTIES
)

add_executable(main_simple_1_nP_ns
    main_simple_1.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_simple_1_nP_ns PUBLIC
    NO_PREMADE_PROPERTIES
    NO_PREMADE_STRATEGIES
)

add_executable(main_simple_1_nP_ns_Ap
    main_simple_1.cpp
    ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp
)
target_compile_definitions(main_simple_1_nP_ns_Ap PUBLIC 
    NO_PREMADE_PROPERTIES
    NO_PREMADE_STRATEGIES
    WITH_ADD_PROPERTIES
)
