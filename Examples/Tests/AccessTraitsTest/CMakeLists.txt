add_executable(CustomAccessTest
    ${PROJECT_SOURCE_DIR}/Object/Object.cpp
    ../mainTest.cpp
    CustomAccessTest.cpp)

target_link_libraries(CustomAccessTest PRIVATE 
    -lgtest
    -lgmock)

add_test(NAME CustomAccessTest COMMAND CustomAccessTest --gtest_color=yes)
