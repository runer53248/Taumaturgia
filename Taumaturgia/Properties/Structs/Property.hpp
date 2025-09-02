#pragma once
#include <numeric>
#include "Taumaturgia/Properties/Helpers/property_helpers.hpp"

static_assert(std::is_same_v<boost::mp11::mp_clear<order_list>, taged_list<>>);  // order_list is taged_list
// static_assert(boost::mp11::mp_size<order_list>::value);                          // order_list is not empty

constexpr static auto properties_counter = boost::mp11::mp_size<order_list>::value;

template <template <typename...> typename property>
    requires is_property<property>
struct Property_ordered {
private:
    static constinit const size_t index = []() {
        return boost::mp11::mp_find<order_list, helpers::most_improved<property>>::value;
    }();

public:
    static constexpr size_t value = (properties_counter > index) ? index + 1 : std::numeric_limits<size_t>::max();  // index of property starting from 1 (or max if not found)
    template <typename T>
    using apply = property<T>;

    using hold_type = property<tag>::hold_type;
    using property_data = property<tag>::property_data;
    using tags_list = property<tag>::property_data::tags_list;

    template <template <typename...> typename P>
        requires is_property<P>
    using property_type = Property_ordered<P>;  // use same Property_ordered or Property_unordered

    template <template <typename...> typename property_other>
    constexpr bool operator==([[maybe_unused]] const Property_ordered<property_other>&) const {
        using other_type = Property_ordered<property_other>;

        if constexpr (
            std::same_as<hold_type, typename other_type::hold_type>              // same hold_type
            and std::same_as<property_data, typename other_type::property_data>  // same property_data
            and std::same_as<tags_list, typename other_type::tags_list>          // same tags_list
            and not(std::same_as<
                        apply<apply<tag>>,
                        apply<tag>> xor
                    std::same_as<
                        typename other_type::template apply<typename other_type::template apply<tag>>,
                        typename other_type::template apply<tag>>)  // both apply once or both aren't
        ) {
            return true;
        } else {
            return false;
        }
    }
};

template <template <typename...> typename property>
    requires is_property<property>
struct Property_unordered {
public:
    static constexpr size_t value = std::numeric_limits<size_t>::max();
    template <typename T>
    using apply = property<T>;

    using hold_type = property<tag>::hold_type;
    using property_data = property<tag>::property_data;
    using tags_list = property<tag>::property_data::tags_list;

    template <template <typename...> typename P>
        requires is_property<P>
    using property_type = Property_unordered<P>;  // use same Property_ordered or Property_unordered

    template <template <typename...> typename property_other>
    constexpr bool operator==([[maybe_unused]] const Property_unordered<property_other>&) const {
        using other_type = Property_unordered<property_other>;

        if constexpr (
            std::same_as<hold_type, typename other_type::hold_type>              // same hold_type
            and std::same_as<property_data, typename other_type::property_data>  // same property_data
            and std::same_as<tags_list, typename other_type::tags_list>          // same tags_list
            and not(std::same_as<
                        apply<apply<tag>>,
                        apply<tag>> xor
                    std::same_as<
                        typename other_type::template apply<typename other_type::template apply<tag>>,
                        typename other_type::template apply<tag>>)  // both apply once or both aren't
        ) {
            return true;
        } else {
            return false;
        }
    }
};

template <template <template <typename...> typename> typename PROP_TYPE>
concept is_property_type = (std::same_as<
                                PROP_TYPE<empty_property>,
                                Property_ordered<empty_property>> or
                            std::same_as<
                                PROP_TYPE<empty_property>,
                                Property_unordered<empty_property>>);
