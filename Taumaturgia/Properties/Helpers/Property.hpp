#pragma once
#include <numeric>
#include "property_helpers.hpp"

static_assert(std::is_same_v<boost::mp11::mp_clear<order_list>, taged_list<>>);  // order_list is taged_list
static_assert(boost::mp11::mp_size<order_list>::value);                          // order_list is not empty

constexpr static auto properties_counter = boost::mp11::mp_size<order_list>::value;

template <template <typename...> typename property>
    requires is_property<property>
class Property {
private:
    static constinit const size_t index = []() {
        return boost::mp11::mp_find<order_list, helpers::best_property_tag<property>>::value;
    }();

public:
    static constexpr size_t value = (properties_counter > index) ? index + 1 : std::numeric_limits<size_t>::max();  // index of property starting from 1 (or max if not found)
    template <typename T>
    using type = property<T>;
};
