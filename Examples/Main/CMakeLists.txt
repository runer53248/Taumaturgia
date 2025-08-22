add_executable(main2_${addons} main2.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
add_executable(main3_${addons} main3.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
add_executable(main4_${addons} main4.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)
add_executable(main5_${addons} main5.cpp ${PROJECT_SOURCE_DIR}/Taumaturgia/Object/Object.cpp)

# get_property(TGTS DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
# foreach(TGT IN LISTS TGTS)
#     message(STATUS "<> Target: ${TGT}")
# endforeach()

print_all_targets(${CMAKE_CURRENT_SOURCE_DIR})
