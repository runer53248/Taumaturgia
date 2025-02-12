#pragma once
#include "Taumaturgia/Properties/UserProperty.hpp"  // for UserPropertyAdapter
#include "Usage/Properties.hpp"
#include "taged_list.hpp"

#ifdef IGNORE_ORDER_LIST
constexpr bool ignore_order_list = true;
#else
constexpr bool ignore_order_list = false;
#endif

template <typename T, template <typename...> typename... properties>
using creator_add_properties = std::conditional_t<
    ignore_order_list,
    add_properties_unordered<T, properties...>,
    add_properties_ordered<T, properties...>>;

//************************************************************************ */
#include "pipeing_with_create.hpp"
//************************************************************************ */
#include "pipeing_with_creator.hpp"
//************************************************************************ */
#include "pipeing_with_property_list.hpp"
