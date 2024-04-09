#pragma once
#include <concepts>

template <typename... T>
struct list {};

struct tag {};

template <typename T>
struct property_tag : public T {};

template <template <typename...> typename T>
concept is_inner_reduction = std::same_as<T<T<property_tag<T<T<tag>>>>>, property_tag<T<tag>>>;

template <template <typename...> typename T>
concept is_property = requires {
    typename T<tag>::property_data;
};

template <template <typename...> typename T>
concept is_property_with_inner_reduction = is_property<T> and is_inner_reduction<T>;

template <template <typename...> typename... properties>
    requires(is_property_with_inner_reduction<properties> and ...)
using taged_list = list<properties<tag>...>;
