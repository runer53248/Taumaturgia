#pragma once
#include "Taumaturgia/Concepts/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/NameTraits.hpp"

template <typename T>
concept Namingable = trait_access_covertable<T, traits::accessName, std::string>;
