#pragma once
#include <boost/mp11.hpp>

template <typename T, size_t N = 0, typename L = std::tuple<>>
struct AsTuple_impl;

template <typename T, size_t N, typename L>
struct AsTuple_impl {
    using type = L;
};

template <size_t N, typename L, typename... Ts>
struct AsTuple_impl<std::tuple<Ts...>, N, L> {
    using type = std::tuple<Ts...>;
};

template <typename T, size_t N, typename L>
    requires requires { getType<N>(std::declval<T>()); }
struct AsTuple_impl<T, N, L> {
    using current_type = std::remove_cvref_t<decltype(getType<N>(std::declval<T>()))>;
    using new_list = boost::mp11::mp_push_back<L, current_type>;
    using type = typename AsTuple_impl<T, N + 1, new_list>::type;
};

template <typename T, size_t N = 0, typename L = std::tuple<>>
using as_tuple = AsTuple_impl<T, N, L>::type;
