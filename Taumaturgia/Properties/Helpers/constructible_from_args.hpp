#pragma once
#include <boost/mp11.hpp>
#include <type_traits>

template <typename... T>
struct list;

template <typename TYPE, typename... ARGS>
concept constructible_from_args = std::is_constructible_v<TYPE, ARGS...> and sizeof...(ARGS) > 0;

template <typename... V>
concept variadic_not_empty = (sizeof...(V) > 0);

template <typename T, typename... V>
concept variadic_contains = boost::mp11::mp_contains<list<V...>, T>::value;

template <typename T, typename... V>
concept contains_type = variadic_contains<T, V...> and variadic_not_empty<V...>;

template <typename T, typename... V>
concept not_contains_type = not variadic_contains<T, V...> and variadic_not_empty<V...>;
