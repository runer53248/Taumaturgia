#pragma once
#include "best_property_tag.hpp"

namespace helpers {

template <template <typename...> typename property>
concept have_improvement_of_property = have_property<typename property<tag>::improvement_of>;  // improvement_of have property_data;

template <template <typename...> typename property>
concept is_property_improvement_possibly_self = is_property<property>                        // property have property_data
                                                and have_improvement_of_property<property>;  // property<tag>::improvement_of have property_data

template <template <typename...> typename property>
concept is_property_improvement = is_property_improvement_possibly_self<property>  //
                                  and not impl::self_improvement<property<tag>>;   // property<tag> != property<tag>::improvement_of

template <typename A, typename B>
struct same_priority {
    static constinit const bool value = []() {
        if constexpr (std::is_same_v<A, B>) {
            return true;
        }
        if constexpr (A::value != std::numeric_limits<size_t>::max()) {  // compare two ordered Properties
            return (A::value == B::value);
        }
        // same_priority true if any improved unordered Property improvement_of same as other
        if constexpr (is_property_improvement_possibly_self<A::template type> or is_property_improvement_possibly_self<B::template type>) {
            return (std::is_same_v<
                    best_property_tag<A::template type>,
                    best_property_tag<B::template type>>);
        }
        return false;
    }();
};

template <typename A, typename B>
concept is_same_priority = same_priority<A, B>::value;

}  // namespace helpers
