#pragma once

// is_base_of_template
template <template <typename> class base, typename derived>
struct is_base_of_template_impl {
    template <typename T>
    static constexpr std::true_type test(const base<T>*);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template <template <typename> class base, typename derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;
