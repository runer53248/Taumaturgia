add_executable(have_get_features_Test_${addons}
have_get_features_Test.cpp)
target_link_libraries(have_get_features_Test_${addons} PRIVATE 
    GTest::GTest GTest::Main)
add_test(NAME have_get_features_Test_${addons} COMMAND have_get_features_Test_${addons} --gtest_color=yes)
