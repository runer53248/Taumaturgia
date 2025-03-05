#pragma once
#include "Taumaturgia/Properties/Helpers/taged_list.hpp"
#include "PropertyFor.hpp"

template <template <typename...> typename property>
    requires is_property<property>
struct Property;

template <template <typename...> typename property>
    requires is_property<property>
struct Property_unordered;

template <const char* NAME, template <typename...> typename property, typename T, typename... Args>
struct PropertyData {
    using property_type = Property<property>;
    using unordered_property_type = Property_unordered<property>;
    using base_type = T;
    using tags_list = list<Args...>;
    static consteval auto name() noexcept {
        if constexpr (NAME != nullptr) {
            return NAME;
        }
        return "";
    }
};
