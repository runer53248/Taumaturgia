add_executable(main_small_${addons} main_small.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
add_executable(a_main_${addons} main.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)

if(NOT DEFINED WITH_ADD_PROPERTIES) # ignore aP versions - not needed
    add_executable(main_simple_1_${addons} main_simple_1.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
    add_executable(a_main_part_${addons} main_part.cpp)
endif()
    
# get_property(TGTS DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
# foreach(TGT IN LISTS TGTS)
#     message(STATUS "<> Target: ${TGT}")
# endforeach()

print_all_targets(${CMAKE_CURRENT_SOURCE_DIR})
