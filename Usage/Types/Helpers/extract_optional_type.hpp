#pragma once
#include "optional_get_variant.hpp"
#include "properties_info.hpp"

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
template <typename TYPE>
constexpr decltype(auto) extract_optional_type(is_optional_get_variant auto&& opt_variant) {
    return opt_variant.transform([](auto&& var_ref) {
        using type = std::conditional_t<
            std::is_same_v<
                std::remove_cvref_t<decltype(var_ref)>,
                get_variant_const_type>,
            const TYPE,
            TYPE>;
        return std::get<std::reference_wrapper<type>>(std::move(var_ref));
    });
}

}  // namespace impl

template <Properties PROPERTY>
constexpr decltype(auto) extract_optional_type(is_optional_get_variant auto&& opt_variant) {
    return impl::extract_optional_type<properties_type<PROPERTY>>(opt_variant);
}
