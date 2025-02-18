cmake_minimum_required(VERSION 3.5)
project(Taumaturgia)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# message("Your C++ compiler supports these C++ features:")
# foreach(i ${CMAKE_CXX_COMPILE_FEATURES})
#   message("${i}")
# endforeach()

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
    # -Wshadow
    
    # -Wno-missing-braces
    -Wno-changes-meaning
    # -fsanitize=undefined
)

# link_libraries(-lubsan)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_definitions(
  # ACCESS_TRAIT_MACRO
)

add_subdirectory(Examples/Simple_1)

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(Examples/nn)
add_subdirectory(Examples/nP)
add_subdirectory(Examples/nS)
add_subdirectory(Examples/nPnS)
