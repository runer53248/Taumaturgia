#pragma once
#include <string>
#include "Concepts/NameConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#include "accessName.hpp"

using Namingable_trait = traits::accessName;
template <typename T>
concept Namingable = trait_access_covertable<T, Namingable_trait, std::string>;
