add_executable(CustomAccessTest-ArmorWear
    ../mainTest.cpp
    "CustomAccessTest ArmorWear.cpp")
target_link_libraries(CustomAccessTest-ArmorWear PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-ArmorWear COMMAND CustomAccessTest-ArmorWear --gtest_color=yes)

add_executable(CustomAccessTest-CureHealth
    ../mainTest.cpp
    "CustomAccessTest CureHealth.cpp")
target_link_libraries(CustomAccessTest-CureHealth PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-CureHealth COMMAND CustomAccessTest-CureHealth --gtest_color=yes)

add_executable(CustomAccessTest-Damage
    ../mainTest.cpp
    "CustomAccessTest Damage.cpp")
target_link_libraries(CustomAccessTest-Damage PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-Damage COMMAND CustomAccessTest-Damage --gtest_color=yes)

add_executable(CustomAccessTest-Health
    ../mainTest.cpp
    "CustomAccessTest Health.cpp")
target_link_libraries(CustomAccessTest-Health PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-Health COMMAND CustomAccessTest-Health --gtest_color=yes)

add_executable(CustomAccessTest-Name
    ../mainTest.cpp
    "CustomAccessTest Name.cpp")
target_link_libraries(CustomAccessTest-Name PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-Name COMMAND CustomAccessTest-Name --gtest_color=yes)

add_executable(CustomAccessTest-Protection
    ../mainTest.cpp
    "CustomAccessTest Protection.cpp")
target_link_libraries(CustomAccessTest-Protection PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-Protection COMMAND CustomAccessTest-Protection --gtest_color=yes)

add_executable(CustomAccessTest-Restore
    ../mainTest.cpp
    "CustomAccessTest Restore.cpp")
target_link_libraries(CustomAccessTest-Restore PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-Restore COMMAND CustomAccessTest-Restore --gtest_color=yes)

add_executable(CustomAccessTest-UserType
    ../mainTest.cpp
    "CustomAccessTest UserType.cpp")
target_link_libraries(CustomAccessTest-UserType PRIVATE 
    -lgtest
    -lgmock)
add_test(NAME CustomAccessTest-UserType COMMAND CustomAccessTest-UserType --gtest_color=yes)
