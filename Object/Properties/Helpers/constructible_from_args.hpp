#pragma once
#include <type_traits>

template <typename... T>
struct list;

template <typename TYPE,typename... ARGS>
concept constructible_from_args = std::is_constructible_v<TYPE, ARGS...> and sizeof...(ARGS) > 0;

template <typename T, typename... V>
concept type_contained = boost::mp11::mp_contains<list<V...>, T>::value;

template <typename T, typename... V>
concept type_is_possible = (type_contained<T, V...> and (sizeof...(V) > 0));

template <typename T, typename... V>
concept type_is_not_possible = (not type_contained<T, V...> and (sizeof...(V) > 0));
