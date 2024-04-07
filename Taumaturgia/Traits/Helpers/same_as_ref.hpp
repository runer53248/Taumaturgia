#pragma once
#include <type_traits>

template <typename T, typename TYPE>
concept same_as_ref = std::same_as<T, TYPE&> or std::same_as<T, const TYPE&>;
