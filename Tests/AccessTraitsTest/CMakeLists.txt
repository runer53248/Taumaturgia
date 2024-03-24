add_executable(CustomAccessTest-ArmorWear
    "CustomAccessTest ArmorWear.cpp")
target_link_libraries(CustomAccessTest-ArmorWear PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-ArmorWear COMMAND CustomAccessTest-ArmorWear --gtest_color=yes)

add_executable(CustomAccessTest-CureHealth
    "CustomAccessTest CureHealth.cpp")
target_link_libraries(CustomAccessTest-CureHealth PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-CureHealth COMMAND CustomAccessTest-CureHealth --gtest_color=yes)

add_executable(CustomAccessTest-Damage
    "CustomAccessTest Damage.cpp")
target_link_libraries(CustomAccessTest-Damage PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Damage COMMAND CustomAccessTest-Damage --gtest_color=yes)

add_executable(CustomAccessTest-Health
    "CustomAccessTest Health.cpp")
target_link_libraries(CustomAccessTest-Health PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Health COMMAND CustomAccessTest-Health --gtest_color=yes)

add_executable(CustomAccessTest-Name
    "CustomAccessTest Name.cpp")
target_link_libraries(CustomAccessTest-Name PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Name COMMAND CustomAccessTest-Name --gtest_color=yes)

add_executable(CustomAccessTest-Protection
    "CustomAccessTest Protection.cpp")
target_link_libraries(CustomAccessTest-Protection PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Protection COMMAND CustomAccessTest-Protection --gtest_color=yes)

add_executable(CustomAccessTest-Restore
    "CustomAccessTest Restore.cpp")
target_link_libraries(CustomAccessTest-Restore PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-Restore COMMAND CustomAccessTest-Restore --gtest_color=yes)

add_executable(CustomAccessTest-UserType
    "CustomAccessTest UserType.cpp")
target_link_libraries(CustomAccessTest-UserType PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-UserType COMMAND CustomAccessTest-UserType --gtest_color=yes)

add_executable(CustomAccessTest-UserProperty
    "CustomAccessTest UserProperty.cpp")
target_link_libraries(CustomAccessTest-UserProperty PRIVATE 
    GTest::GTest GTest::gmock_main)
add_test(NAME CustomAccessTest-UserProperty COMMAND CustomAccessTest-UserProperty --gtest_color=yes)
