#pragma once
#include <type_traits>
#include "Traits/NameTraits.hpp"
#include "Types/Name.hpp"

template <typename T>
concept Namingable = requires(std::remove_const_t<T> x, std::add_const_t<T> y) {
    { traits::accessName::get(x) } -> std::convertible_to<std::string>;
    { traits::accessName::get(y) } -> std::convertible_to<const std::string>;
};
