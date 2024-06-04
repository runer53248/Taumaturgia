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
    using add_properties = ::add_properties<T, properties...>;
};
