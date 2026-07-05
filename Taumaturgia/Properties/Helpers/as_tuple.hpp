#pragma once
#include <boost/mp11.hpp>

namespace impl {
template <typename T, size_t N = 0, size_t LIMIT = std::numeric_limits<size_t>::max(), typename L = std::tuple<>>
struct AsTuple_impl;

template <typename T, size_t N, size_t LIMIT, typename L>
struct AsTuple_impl {
    using type = L;
};

template <size_t N, size_t LIMIT, typename L, typename... Ts>
struct AsTuple_impl<std::tuple<Ts...>, N, LIMIT, L> {
    using type = std::tuple<Ts...>;
};

template <typename T, size_t N, size_t LIMIT, typename L>
    requires(requires { getType<N>(std::declval<T>()); } and (N < LIMIT))
struct AsTuple_impl<T, N, LIMIT, L> {
    using current_type = std::remove_cvref_t<decltype(getType<N>(std::declval<T>()))>;
    using new_list = boost::mp11::mp_push_back<L, current_type>;
    using type = typename AsTuple_impl<T, N + 1, LIMIT, new_list>::type;
};
}  // namespace impl

template <typename T, size_t SKIP = 0, size_t LIMIT = std::numeric_limits<size_t>::max()>
using as_tuple = impl::AsTuple_impl<T, SKIP, std::max(LIMIT, LIMIT + SKIP), std::tuple<>>::type;
