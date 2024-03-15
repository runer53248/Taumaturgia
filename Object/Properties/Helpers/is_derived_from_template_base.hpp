#pragma once
#include <type_traits>

template <typename derived, template <typename> typename base>
struct is_derived_from_template_base_impl {
    template <typename T>
    static constexpr std::true_type test(const base<T>*);        // for properties (ie. impl::Wearing_<T>)
    static constexpr std::true_type test(const base<derived>*);  // for conditional properties aliases (ie. Wearing<T>)
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<const derived*>()));
};

template <typename derived, template <typename> typename base>
using is_derived_from_template_base = typename is_derived_from_template_base_impl<derived, base>::type;

template <typename T, template <typename> typename base>
concept derived_from_template_base = is_derived_from_template_base<T, base>::value;
