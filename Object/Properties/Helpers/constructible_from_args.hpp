#pragma once
#include <type_traits>

template <typename TYPE,typename... ARGS>
concept constructible_from_args = std::is_constructible_v<TYPE, ARGS...> and sizeof...(ARGS) > 0;
