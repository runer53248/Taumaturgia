#pragma once
#include <type_traits>

template <typename derived, template <typename> class base>
struct is_derived_from_template_base_impl {
    template <typename T>
    static constexpr std::true_type test(const base<T>*);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<const derived*>()));
};

template <typename derived, template <typename> class base>
using is_derived_from_template_base = typename is_derived_from_template_base_impl<derived, base>::type;

template <class T, template <typename> class base>
concept derived_from_template_base = is_derived_from_template_base<T, base>::value;
