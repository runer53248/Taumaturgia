add_executable(1_pipe_introduction_${addons}
    pipeing/pipe_introduction.cpp
)
add_executable(2_traits_introduction_${addons}
    traits/traits_introduction.cpp
)
add_executable(3_order_list_introduction_${addons}
    order_list/order_list_introduction.cpp
)
add_executable(3_2_order_list_introduction_${addons}
    order_list/order_list_introduction_2.cpp
)
add_executable(4_tags_introduction_${addons}
    tags/tags_introduction.cpp
)
add_executable(5_default_values_${addons}
default_values/default_values.cpp
)
add_executable(5_default_values2_${addons}
default_values/default_values2.cpp
)
add_executable(5_default_values3_${addons}
default_values/default_values3.cpp
)
add_executable(6_general_features_${addons}
general_features/general_features.cpp
)

target_link_libraries(4_tags_introduction_${addons} PRIVATE "-lstdc++exp")
target_link_libraries(5_default_values_${addons} PRIVATE "-lstdc++exp")
target_link_libraries(5_default_values2_${addons} PRIVATE "-lstdc++exp")
target_link_libraries(5_default_values3_${addons} PRIVATE "-lstdc++exp")
target_link_libraries(6_general_features_${addons} PRIVATE "-lstdc++exp")