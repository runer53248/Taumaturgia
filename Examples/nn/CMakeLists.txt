add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Main Main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../MainExamples MainExamples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple Simple)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Introduction Introduction)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Features Features)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Introduction Introduction2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Tests Tests)

add_executable(111 ../MainExamples/main-delete.cpp)
add_executable(112 ../MainExamples/main-delete.cpp)
target_compile_definitions(112 PUBLIC NO_PREMADE_PROPERTIES)
add_executable(113 ../MainExamples/main-example.cpp)
add_executable(114 ../MainExamples/main-example2.cpp)