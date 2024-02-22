#pragma once
#include <type_traits>
#include "Traits/NameTraits.hpp"
#include "Types/Name.hpp"

template <typename T>
concept Namingable = requires(std::remove_cvref_t<T> x) {
    { traits::accessName::get(x) } -> std::convertible_to<std::string>;
    { traits::accessName::get(std::as_const(x)) } -> std::convertible_to<const std::string>;
};
