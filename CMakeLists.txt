cmake_minimum_required(VERSION 3.21)
project (Taumaturgia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -fwrapv
    -Wall 
    -Wextra 
    -Wsign-compare
    -Wsign-conversion
    -Wconversion
    -pedantic
    -Werror
)

include_directories(${Taumaturgia_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    Examples/Main/main.cpp
    Object/Object.cpp
)
add_executable(${PROJECT_NAME}_simple
    Examples/Simple/main_simple.cpp
    Object/Object.cpp
)
add_executable(${PROJECT_NAME}-minimal
    Examples/Minimal/main_minimal.cpp
    Object/Object.cpp
)
add_executable(${PROJECT_NAME}-test
    Examples/Tests/main_tests.cpp
    Object/Object.cpp
)

enable_testing()
add_subdirectory(Examples/Tests)
