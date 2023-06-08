#pragma once
#include <type_traits>
#include "Traits/NameTraits.hpp"
#include "Types/Name.hpp"

template <typename T>
concept Namingable = requires(T t) {
    { traits::accessName::get(t) } -> std::convertible_to<std::string>;
};
