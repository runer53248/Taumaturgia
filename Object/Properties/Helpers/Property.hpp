#pragma once
#include <numeric>
#include "property_helpers.hpp"

static_assert(std::is_same_v<mp_clear<order_list>, taged_list<>>);
static_assert(mp_size<order_list>::value);

constexpr static auto properties_counter = mp_size<order_list>::value;

template <template <typename...> typename property>
    requires is_property<property>
struct Property {
private:
    // constinit const static auto index = mp_find<order_list, property<tag>>::value;
    constinit const static auto index = []() -> size_t {
        if constexpr (helpers::is_property_improvement<property>) {
            return mp_find<order_list, typename property<tag>::improvement_of>::value; // same priority for improved ordered properties
        } 
        return mp_find<order_list, property<tag>>::value;
    }();

public:
    constexpr static auto value = (properties_counter > index) ? index + 1 : std::numeric_limits<size_t>::max(); // index of property starting from 1 (or max if not found)
    template <typename T>
    using type = property<T>;
};
