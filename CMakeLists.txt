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

    -Wno-defaulted-function-deleted
    -Wno-missing-braces
)

include_directories(${Taumaturgia_SOURCE_DIR})

enable_testing()
add_subdirectory(Examples)
add_subdirectory(Tests)
