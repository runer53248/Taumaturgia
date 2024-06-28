#pragma once
#include "optional_get_variant.hpp"

//         Properties
//             |
//       properties_info
//             |
//       list_of_types
//             |
//    optional_get_variant
//             |
//   extract_optional_type

namespace impl {

// TODO: check get type
// requires T is holded by opt_variant
// input:   optional<variant<..., reference_wrapper<(possibly const) TYPE>, ...>>
// output:  optional<reference_wrapper<(possibly const) TYPE>>
template <typename TYPE, is_optional_get_variant INPUT>
constexpr decltype(auto) extract_optional_type(INPUT&& opt_variant) {
    return opt_variant.transform([]<is_get_variant T>(T&& var_ref) {
        using ref_type = std::reference_wrapper<
        std::conditional_t<
            std::is_same_v<
                std::remove_cvref_t<T>,
                get_variant_const_type>,
            const TYPE,
            TYPE>>;
        return std::get<ref_type>(std::move(var_ref));
    });
}

}  // namespace impl

template <Properties PROPERTY>
constexpr decltype(auto) extract_optional_type(is_optional_get_variant auto&& opt_variant) {
    return impl::extract_optional_type<properties_type<PROPERTY>>(opt_variant);
}
