#pragma once
#include "taged_list.hpp"

template <template <typename...> typename property>
    requires is_property<property>
struct Property;

template <const char* NAME, template <typename...> typename property, typename T, typename... Args>
struct PropertyData {
    using property_type = Property<property>;
    using base_type = T;
    using tags_list = list<Args...>;
    static consteval auto name() noexcept {
        if constexpr (NAME != nullptr) {
            return NAME;
        }
        return "";
    }
};
