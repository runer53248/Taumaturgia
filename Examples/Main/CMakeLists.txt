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
target_compile_definitions(${PROJECT_NAME}-3 PUBLIC USER_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-4 PUBLIC WITH_ADD_PROPERTIES USER_PROPERTIES)

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
target_compile_definitions(${PROJECT_NAME}-3-simple PUBLIC USER_PROPERTIES)
target_compile_definitions(${PROJECT_NAME}-4-simple PUBLIC WITH_ADD_PROPERTIES USER_PROPERTIES)