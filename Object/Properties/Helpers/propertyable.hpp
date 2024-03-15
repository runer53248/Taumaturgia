#pragma once
#include <type_traits>

template <typename T, template <typename> typename property>
concept propertyable = requires(T x) {
    std::is_nothrow_convertible_v<T, property<T>>;
};
