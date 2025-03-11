#pragma once
#include <numeric>
#include "Taumaturgia/Properties/Helpers/property_helpers.hpp"

static_assert(std::is_same_v<boost::mp11::mp_clear<order_list>, taged_list<>>);  // order_list is taged_list
// static_assert(boost::mp11::mp_size<order_list>::value);                          // order_list is not empty

constexpr static auto properties_counter = boost::mp11::mp_size<order_list>::value;

template <template <typename...> typename property>
    requires is_property<property>
struct Property {
private:
    static constinit const size_t index = []() {
        return boost::mp11::mp_find<order_list, helpers::most_improved<property>>::value;
    }();

public:
    static constexpr size_t value = (properties_counter > index) ? index + 1 : std::numeric_limits<size_t>::max();  // index of property starting from 1 (or max if not found)
    template <typename T>
    using apply = property<T>;

    template <template <typename...> typename P>
        requires is_property<P>
    using property_type = Property<P>;
};

template <template <typename...> typename property>
    requires is_property<property>
struct Property_unordered {
public:
    static constexpr size_t value = std::numeric_limits<size_t>::max();
    template <typename T>
    using apply = property<T>;

    template <template <typename...> typename P>
        requires is_property<P>
    using property_type = Property_unordered<P>;
};

template <template <template <typename...> typename> typename PROP_TYPE>
concept is_property_type = (std::same_as<
                                PROP_TYPE<empty_property>,
                                Property<empty_property>> or
                            std::same_as<
                                PROP_TYPE<empty_property>,
                                Property_unordered<empty_property>>);
