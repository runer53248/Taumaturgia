add_compile_definitions(NO_PREMADE_PROPERTIES)
set(NO_PREMADE_PROPERTIES "nP")

set(addons ${NO_PREMADE_PROPERTIES}${NO_PREMADE_STRATEGIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple_1 Simple_1)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Main Main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../MainExamples MainExamples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple Simple)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Introduction Introduction)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Features Features)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Introduction Introduction2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Tests Tests)
