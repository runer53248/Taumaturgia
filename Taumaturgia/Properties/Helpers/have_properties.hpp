#pragma once
#include <limits>
#include "property_helpers.hpp"

namespace helpers {

template <template <typename...> typename property>
    requires is_property<property>
class equivalent_properties_predicate {
private:
    template <typename lhp, typename rhp>
    struct equivalent_properties_predicate_impl {
        static constexpr bool value =
            // (std::is_same_v<lhp, rhp>) or                                                       // same property
            (std::is_same_v<typename lhp::template type<tag>, typename rhp::template type<tag>>) or  // same Property or UserProperty (eg. UserProperty_<int, tag>)
            ((lhp::value == rhp::value) and lhp::value != std::numeric_limits<size_t>::max());       // same priority of known property
    };

public:
    template <typename T>
    using type = equivalent_properties_predicate_impl<T, Property<property>>;
};

}  // namespace helpers

template <typename T, template <typename...> typename... properties>
concept have_properties =
    (is_property<properties> and ...) and
    boost::mp11::mp_and<
        boost::mp11::mp_to_bool<
            boost::mp11::mp_count_if<
                typename helpers::Scheme<T>::list_t,
                helpers::equivalent_properties_predicate<properties>::template type>>...>::value;
