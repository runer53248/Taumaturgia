function(print_all_targets DIR)
    get_property(TGTS DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)

    foreach(TGT IN LISTS TGTS)
        message(STATUS "Target: ${TGT}")

        add_custom_target(
            copy-executable-${TGT}
            ALL
            DEPENDS 
                $<TARGET_FILE:${TGT}>
            COMMAND
                ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${TGT}> ${CMAKE_BINARY_DIR}/COMPARE/EXEC
        )

        add_custom_target(
            run-text-${TGT}
            ALL
            DEPENDS 
                copy-executable-${TGT}
            COMMAND
                ${CMAKE_BINARY_DIR}/COMPARE/EXEC/${TGT} --gtest_color=yes > ${CMAKE_BINARY_DIR}/COMPARE/TXT/${TGT}.txt
        )

        add_custom_target(
            html-${TGT}${ID}
            ALL
            DEPENDS run-text-${TGT}
            COMMAND
                ansi2html < ${CMAKE_BINARY_DIR}/COMPARE/TXT/${TGT}.txt > ${CMAKE_BINARY_DIR}/COMPARE/HTML/${TGT}.html
        )
    endforeach()

    get_property(SUBDIRS DIRECTORY "${DIR}" PROPERTY SUBDIRECTORIES)

    foreach(SUBDIR IN LISTS SUBDIRS)
        print_all_targets("${SUBDIR}")
    endforeach()
endfunction()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Main Main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple Simple)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Simple_1 Simple_1)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../MainExamples MainExamples)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Features Features)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Tests Tests)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Introduction Introduction)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../Introduction Introduction2)
