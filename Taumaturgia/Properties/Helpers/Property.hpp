#pragma once
#include <numeric>
#include "property_helpers.hpp"

static_assert(std::is_same_v<mp_clear<order_list>, taged_list<>>);  // order_list is taged_list
static_assert(mp_size<order_list>::value);                          // order_list is not empty

constexpr static auto properties_counter = mp_size<order_list>::value;

template <template <typename...> typename property>
    requires is_property<property>
class Property {
private:
    constinit const static size_t index = []() {
        return mp_find<order_list, helpers::best_property_tag<property>>::value;
    }();

public:
    static constexpr auto value = (properties_counter > index) ? index + 1 : std::numeric_limits<size_t>::max();  // index of property starting from 1 (or max if not found)
    template <typename T>
    using type = property<T>;
};
