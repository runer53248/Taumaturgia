#pragma once
#include <numeric>
#include "property_helpers.hpp"

static_assert(std::is_same_v<mp_clear<order_list>, taged_list<>>);
static_assert(mp_size<order_list>::value);

template <template <typename> typename property>
struct Property {
private:
    constexpr static auto size = mp_size<order_list>::value;
    constexpr static auto index = mp_find<order_list, property<tag>>::value;

public:
    constexpr static auto value = (size > index) ? index + 1 : std::numeric_limits<size_t>::max(); // index of property starting from 1 (or max if not found)
    template <typename T>
    using type = property<T>;
};