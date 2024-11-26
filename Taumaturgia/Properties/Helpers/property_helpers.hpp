#pragma once
#include "add_properties.hpp"

//       taged_list        build_into_t
//            |                  |
//      most_improved            |
//            |                  |
//       same_priority           |
//            |                  |
// create_ordered_property_list  /
//            |                 /
//         Scheme              /
//              \             /
//              add_properties

template <template <typename...> typename... properties>
    requires(is_property<properties> and ...)
struct properties_list {
    template <typename T>
    using apply_ordered_properties_to = ::add_properties_ordered<T, properties...>;

    template <typename T>
    using apply_unordered_properties_to = ::add_properties_unordered<T, properties...>;

    template <typename T, bool ORDERED = true>
    using apply_properties_to = std::conditional_t<
        ORDERED,
        ::add_properties_ordered<T, properties...>,
        ::add_properties_unordered<T, properties...>>;
};
