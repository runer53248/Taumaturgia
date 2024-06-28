#pragma once
#include "Taumaturgia/Strategies/GetStrategy.hpp"
#include "Usage/Types/Enums/Properties.hpp"

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
using get_result_type = std::optional<std::reference_wrapper<
    std::conditional_t<
        std::is_const_v<GET_TYPE>,
        const properties_type<PROPERTY>,
        properties_type<PROPERTY>>>>;

template <Properties PROPERTY, Gettingable GET_TYPE>
inline constexpr auto default_get_behavior(GET_TYPE& obj) -> get_result_type<PROPERTY, GET_TYPE> {
    if constexpr (is_properties_accessable<PROPERTY, GET_TYPE>) {
        return std::optional{std::ref(properties_trait<PROPERTY>::get(obj))};
    }
    return {};
}
