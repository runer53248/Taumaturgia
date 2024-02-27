#pragma once

template <template <typename...> typename property>
struct Property;

template <const char* NAME, template <typename...> typename property, typename T>
struct PropertyData {
    using base_type = T;
    using property_type = Property<property>;
    static consteval auto name() noexcept {
        if constexpr (NAME != nullptr) {
            return NAME;
        }
        return "";
    }
};
