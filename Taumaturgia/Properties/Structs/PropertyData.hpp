#pragma once
#include "Taumaturgia/Properties/Helpers/taged_list.hpp"

template <template <typename...> typename property>
    requires is_property<property>
struct Property_ordered;

template <template <typename...> typename property>
    requires is_property<property>
struct Property_unordered;

template <template <typename...> typename property, typename T, typename... Args>
struct PropertyData {
    using ordered_property_type = Property_ordered<property>;
    using unordered_property_type = Property_unordered<property>;
    using base_type = T;
    using tags_list = list<Args...>;
};
