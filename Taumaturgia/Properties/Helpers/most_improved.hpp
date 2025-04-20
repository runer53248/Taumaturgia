#pragma once
#include "taged_list.hpp"

namespace helpers::impl {
template <typename T>
concept self_improvement = std::same_as<T, typename T::improvement_of>;

template <typename T>
concept have_improvement = requires {
    typename T::improvement_of;
};

template <typename T>
concept improvement = have_improvement<T> and not self_improvement<T>;

template <typename T>
concept not_improvement = not improvement<T>;

template <typename T>
struct most_improved_impl;

template <improvement T>
struct most_improved_impl<T> {
    using type = most_improved_impl<typename T::improvement_of>::type;
};

template <not_improvement T>
struct most_improved_impl<T> {
    using type = T;
};
}  // namespace helpers::impl

namespace helpers {
template <template <typename...> typename T>
using most_improved = impl::most_improved_impl<T<tag>>::type;
}  // namespace helpers
