#pragma once

template <typename... T>
struct list {};

struct tag {};

template <template <typename...> typename T>
concept is_property = requires {
    typename T<tag>::property_data;
};

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
using taged_list = list<properties<tag>...>;
