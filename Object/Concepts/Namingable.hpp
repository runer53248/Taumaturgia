#pragma once
#include "Object/Concepts/Helpers/trait_accessable.hpp"
#include "Object/Concepts/Traits/NameTraits.hpp"

template <typename T>
concept Namingable = trait_access_covertable<T, traits::accessName, std::string>;
