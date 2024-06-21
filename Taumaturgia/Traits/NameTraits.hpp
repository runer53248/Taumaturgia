#pragma once
#include <string>
#include "Helpers/traits_helper.hpp"
#include "Structs/accessName.hpp"

using Namingable_trait = traits::accessName;

template <typename T>
concept Namingable = traits::helpers::trait_access_covertable<T, Namingable_trait, std::string>;
