add_executable(main_small main_small.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)

add_executable(main_simple_1 main_simple_1.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)

add_executable(main_simple_1_Ap main_simple_1.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(main_simple_1_Ap PUBLIC 
    WITH_ADD_PROPERTIES
)

add_executable(main_simple_1_nP_ns main_simple_1.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(main_simple_1_nP_ns PUBLIC
    NO_PREMADE_PROPERTIES
    NO_PREMADE_STRATEGIES
)

add_executable(main_simple_1_nP_ns_Ap main_simple_1.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(main_simple_1_nP_ns_Ap PUBLIC 
    NO_PREMADE_PROPERTIES
    NO_PREMADE_STRATEGIES
    WITH_ADD_PROPERTIES
)

add_executable(a_main_ main.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)

add_executable(a_main_Ap main.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(a_main_Ap PUBLIC WITH_ADD_PROPERTIES)

add_executable(a_main_Np main.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(a_main_Np PUBLIC NO_PREMADE_PROPERTIES)

add_executable(a_main_Ap_Np main.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
target_compile_definitions(a_main_Ap_Np PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(a_main_part_ main_part.cpp)

add_executable(a_main_part_Ap main_part.cpp)
target_compile_definitions(a_main_part_Ap PUBLIC WITH_ADD_PROPERTIES)

add_executable(a_main_part_Np main_part.cpp)
target_compile_definitions(a_main_part_Np PUBLIC NO_PREMADE_PROPERTIES)

add_executable(a_main_part_Ap_Np main_part.cpp)
target_compile_definitions(a_main_part_Ap_Np PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)
