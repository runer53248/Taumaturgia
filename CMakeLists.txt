cmake_minimum_required(VERSION 3.21)
project (Taumaturgia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-test main_tests.cpp)
