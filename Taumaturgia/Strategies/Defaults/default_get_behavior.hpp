#pragma once
#include "Taumaturgia/Strategies/GetStrategy.hpp"
#include "Usage/Enums/Properties.hpp"

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
inline constexpr auto default_get_behavior(GET_TYPE& obj) -> get_result_type<PROPERTY, GET_TYPE> {
    if constexpr (is_properties_accessable<PROPERTY, GET_TYPE>) {
        return std::optional{std::ref(properties_trait<PROPERTY>::get(obj))};
    }
    return {};
}
