#pragma once
#include "Taumaturgia/Strategies/GetStrategy.hpp"
#include "Taumaturgia/Types/Enums/Properties.hpp"

// * this version return optional variant of reference_wraper of types
// template <Properties PROPERTY>
// inline constexpr auto default_get_behavior(Gettingable auto& obj) -> to_optional_get_variant<decltype(obj)> {
//     if constexpr (is_properties_accessable<PROPERTY, decltype(obj)>) {
//         return std::ref(properties_trait<PROPERTY>::get(obj));
//     }
//     return {};
// }

// * this version return optional reference_wraper of type
template <Properties PROPERTY, typename T>
using get_result_type = std::optional<std::reference_wrapper<
    std::conditional_t<
        std::is_const_v<std::remove_reference_t<T>>,
        const properties_type<PROPERTY>,
        properties_type<PROPERTY>>>>;

template <Properties PROPERTY>
inline constexpr auto default_get_behavior(Gettingable auto& obj) -> get_result_type<PROPERTY, decltype(obj)>{
    if constexpr (is_properties_accessable<PROPERTY, decltype(obj)>) {
        return std::optional{std::ref(properties_trait<PROPERTY>::get(obj))};
    }
    return {};
}
