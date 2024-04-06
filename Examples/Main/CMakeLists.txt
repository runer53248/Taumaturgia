add_executable(${PROJECT_NAME}-1
    main.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-2
    main.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-3
    main.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-4
    main.cpp
    ../../Object/Object.cpp
)
target_compile_definitions(${PROJECT_NAME}-1 PUBLIC)
target_compile_definitions(${PROJECT_NAME}-2 PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-3 PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-4 PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(${PROJECT_NAME}-1-simple
    main_simple.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-2-simple
    main_simple.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-3-simple
    main_simple.cpp
    ../../Object/Object.cpp
)

add_executable(${PROJECT_NAME}-4-simple
    main_simple.cpp
    ../../Object/Object.cpp
)

target_compile_definitions(${PROJECT_NAME}-1-simple PUBLIC)
target_compile_definitions(${PROJECT_NAME}-2-simple PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-3-simple PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-4-simple PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(${PROJECT_NAME}-1-part main_part.cpp)
add_executable(${PROJECT_NAME}-2-part main_part.cpp)
add_executable(${PROJECT_NAME}-3-part main_part.cpp)
add_executable(${PROJECT_NAME}-4-part main_part.cpp)

target_compile_definitions(${PROJECT_NAME}-1-part PUBLIC)
target_compile_definitions(${PROJECT_NAME}-2-part PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-3-part PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-4-part PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(main2
    main2.cpp
    ../../Object/Object.cpp
)

add_executable(main3-1
    main3.cpp
    ../../Object/Object.cpp
)

add_executable(main3-2
    main3.cpp
    ../../Object/Object.cpp
)

add_executable(main3-3
    main3.cpp
    ../../Object/Object.cpp
)

add_executable(main3-4
    main3.cpp
    ../../Object/Object.cpp
)

target_compile_definitions(main3-1 PUBLIC)
target_compile_definitions(main3-2 PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main3-3 PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main3-4 PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(main4-1
    main4.cpp
    ../../Object/Object.cpp
)

add_executable(main4-2
    main4.cpp
    ../../Object/Object.cpp
)

add_executable(main4-3
    main4.cpp
    ../../Object/Object.cpp
)

add_executable(main4-4
    main4.cpp
    ../../Object/Object.cpp
)

target_compile_definitions(main4-1 PUBLIC)
target_compile_definitions(main4-2 PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main4-3 PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main4-4 PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)

add_executable(main5-1
    main5.cpp
    ../../Object/Object.cpp
)

add_executable(main5-2
    main5.cpp
    ../../Object/Object.cpp
)

add_executable(main5-3
    main5.cpp
    ../../Object/Object.cpp
)

add_executable(main5-4
    main5.cpp
    ../../Object/Object.cpp
)

target_compile_definitions(main5-1 PUBLIC)
target_compile_definitions(main5-2 PUBLIC WITH_ADD_PROPERTIES)
target_compile_definitions(main5-3 PUBLIC NO_PREMADE_PROPERTIES)
target_compile_definitions(main5-4 PUBLIC WITH_ADD_PROPERTIES NO_PREMADE_PROPERTIES)