#pragma once
#include <concepts>

struct tag {};

template <typename... T>
struct list {
    list() = default;

    template <typename TT>
    list(const TT&) {}
};

// implicit conversion from Property<ALIAS> to list<Property<ALIAS>>
template <template <template <typename...> typename> typename Prop, template <typename...> typename property>
list(const Prop<property>&) -> list<Prop<property>>;

template <typename T>
concept have_property_data = requires {
    typename T::property_data;
    // typename T::hold_type;
};

class empty_type {};

template <typename T>
struct empty_property : public T {
    using property_data = void;
};

template <template <typename...> typename T>
concept have_inner_reduction_feature = std::same_as<T<T<empty_property<T<T<tag>>>>>, empty_property<T<tag>>>;

template <template <typename...> typename T>
concept is_property = have_property_data<T<tag>>;

template <template <typename...> typename T>
concept is_proper_property = is_property<T> and have_inner_reduction_feature<T>;

template <template <typename...> typename... T>
// requires(is_proper_property<T> and ...) // TODO: fix this
using taged_list = list<T<tag>...>;
