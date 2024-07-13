#pragma once
#include "most_improved.hpp"

namespace helpers::impl {
    template <template <typename...> typename property>
    concept have_improvement_of_property = have_property<typename property<tag>::improvement_of>;  // improvement_of have property_data;

    template <template <typename...> typename property>
    concept is_property_improvement_possibly_self = is_property<property>                        // property have property_data
                                                    and have_improvement_of_property<property>;  // property<tag>::improvement_of have property_data

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
            if constexpr (is_property_improvement_possibly_self<A::template apply> or is_property_improvement_possibly_self<B::template apply>) {
                return (std::is_same_v<
                        most_improved<A::template apply>,
                        most_improved<B::template apply>>);
            }
            return false;
        }();
    };
}  // namespace helpers::impl

namespace helpers {
template <template <typename...> typename property>
concept is_property_improvement = impl::is_property_improvement_possibly_self<property>  //
                                  and not impl::self_improvement<property<tag>>;   // property<tag> != property<tag>::improvement_of

template <typename A, typename B>
concept is_same_priority = impl::same_priority<A, B>::value;
}  // namespace helpers
