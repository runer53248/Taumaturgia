#pragma once
#include <type_traits>
#include "Types/Name.hpp"

template <typename T>
concept Namingable = requires(T t) {
    { t.name } -> std::convertible_to<std::string>;
};
