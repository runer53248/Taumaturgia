#pragma once
#include "Traits/NameTraits.hpp"
#include "trait_accessable.hpp"

template <typename T>
concept Namingable = trait_access_covertable<T, traits::accessName, std::string>;
