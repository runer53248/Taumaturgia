add_executable(CustomAccessTest-ArmorWear_${addons}
    "CustomAccessTest ArmorWear.cpp")
target_link_libraries(CustomAccessTest-ArmorWear_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-ArmorWear COMMAND CustomAccessTest-ArmorWear_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-CureHealth_${addons}
    "CustomAccessTest CureHealth.cpp")
target_link_libraries(CustomAccessTest-CureHealth_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-CureHealth COMMAND CustomAccessTest-CureHealth_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-Damage_${addons}
    "CustomAccessTest Damage.cpp")
target_link_libraries(CustomAccessTest-Damage_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Damage COMMAND CustomAccessTest-Damage_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-Health_${addons}
    "CustomAccessTest Health.cpp")
target_link_libraries(CustomAccessTest-Health_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Health COMMAND CustomAccessTest-Health_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-Name_${addons}
    "CustomAccessTest Name.cpp")
target_link_libraries(CustomAccessTest-Name_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Name COMMAND CustomAccessTest-Name_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-Protection_${addons}
    "CustomAccessTest Protection.cpp")
target_link_libraries(CustomAccessTest-Protection_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Protection COMMAND CustomAccessTest-Protection_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-Restore_${addons}
    "CustomAccessTest Restore.cpp")
target_link_libraries(CustomAccessTest-Restore_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Restore COMMAND CustomAccessTest-Restore_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-UserType_${addons}
    "CustomAccessTest UserType.cpp")
target_link_libraries(CustomAccessTest-UserType_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-UserType COMMAND CustomAccessTest-UserType_${addons} --gtest_color=yes)

add_executable(CustomAccessTest-UserProperty_${addons}
    "CustomAccessTest UserProperty.cpp")
target_link_libraries(CustomAccessTest-UserProperty_${addons} PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-UserProperty COMMAND CustomAccessTest-UserProperty_${addons} --gtest_color=yes)
