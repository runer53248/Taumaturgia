#pragma once

template <typename... T>
struct list {};

struct tag {};

template <template <typename...> typename... T>
using taged_list = list<T<tag>...>;
