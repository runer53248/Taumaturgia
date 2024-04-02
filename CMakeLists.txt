cmake_minimum_required(VERSION 3.5)
project(Taumaturgia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_compile_options(
    -fwrapv
    -Wall 
    -Wextra 
    -Wsign-compare
    -Wsign-conversion
    -Wconversion
    -pedantic
    -Werror

    -Wno-missing-braces
)

add_compile_definitions(ACCESS_TRAIT_MACRO)

include_directories(${Taumaturgia_SOURCE_DIR})

find_package(GTest REQUIRED)

add_subdirectory(Examples)

enable_testing()
add_subdirectory(Tests)
