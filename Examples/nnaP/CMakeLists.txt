add_compile_definitions(WITH_ADD_PROPERTIES)
set(WITH_ADD_PROPERTIES "aP")

set(addons ${NO_PREMADE_PROPERTIES}${NO_PREMADE_STRATEGIES}${WITH_ADD_PROPERTIES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple_1 Simple_1)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Main Main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../MainExamples MainExamples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple Simple)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Introduction Introduction)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Features Features)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Introduction Introduction2)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Tests Tests)
