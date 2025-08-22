if(NOT DEFINED WITH_ADD_PROPERTIES) # ignore aP versions - not needed
    add_executable(improving_${addons} improving.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
endif()

print_all_targets(${CMAKE_CURRENT_SOURCE_DIR})
