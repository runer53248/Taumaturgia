#pragma once

namespace helpers::impl {
template <typename property>
concept self_improvement = std::same_as<property, typename property::improvement_of>;

template <typename property>
concept improvement = requires {
    typename property::improvement_of;
} and not self_improvement<property>;  // property != property::improvement_of

template <typename property>
concept not_improvement = not improvement<property>;

template <typename property>
struct most_improved_helper;

template <improvement property>
struct most_improved_helper<property> {
    using type = most_improved_helper<typename property::improvement_of>::type;
};

template <not_improvement property>
struct most_improved_helper<property> {
    using type = property;
};
}  // namespace helpers::impl

namespace helpers {
template <template <typename...> typename property>
using best_property_tag = impl::most_improved_helper<property<tag>>::type;
}  // namespace helpers
