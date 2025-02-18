add_executable(1_pipe_introduction_${addons}
    pipeing/pipe_introduction.cpp
)
add_executable(2_trait_introduction_${addons}
    traits/traits_introduction.cpp
)
add_executable(3_order_list_introduction_${addons}
    order_list/order_list_introduction.cpp
)
add_executable(4_tags_introduction_${addons}
    tags/tags_introduction.cpp
)
target_link_libraries(4_tags_introduction_${addons} PRIVATE "-lstdc++exp")
