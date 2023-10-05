#pragma once

template <template <typename> typename property>
struct Property;

template <template <typename> typename property, typename T, const char* NAME = nullptr>
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
