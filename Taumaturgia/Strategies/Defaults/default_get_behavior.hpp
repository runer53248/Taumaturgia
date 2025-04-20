#pragma once
#include "Taumaturgia/Strategies/GetterStrategy.hpp"

// * this version return optional variant of reference_wraper of types
// template <Properties PROPERTY, Gettingable GET_TYPE>
// inline constexpr auto default_get_behavior(GET_TYPE& obj) -> to_optional_get_variant<GET_TYPE> {
//     if constexpr (is_properties_accessable<PROPERTY, GET_TYPE>) {
//         return std::ref(properties_trait<PROPERTY>::get(obj));
//     }
//     return {};
// }

// * this version return optional reference_wraper of type
template <Properties PROPERTY, Gettingable GET_TYPE>
inline constexpr auto default_get_behavior(GET_TYPE& obj) -> get_result_type<PROPERTY, std::is_const_v<GET_TYPE>> {
    if constexpr (is_properties_accessable<PROPERTY, GET_TYPE>) {
        decltype(auto) result = properties_trait<PROPERTY>::get(obj);  // will call get even when result be not used
        if constexpr (std::is_same_v<
                          std::optional<std::reference_wrapper<std::remove_reference_t<decltype(result)>>>,
                          get_result_type<PROPERTY, std::is_const_v<GET_TYPE>>>) {
            return std::optional{std::ref(result)};
        }
        // ignore convertible properties
    }
    return {};
}
