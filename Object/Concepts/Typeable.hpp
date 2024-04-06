#pragma once
#include "Traits/UserTypeTraits.hpp"
#include "trait_accessible.hpp"

template <typename T, typename RESULT_TYPE>
concept getType_or_custom_accessable = trait_accessible<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_able = traits::GetTypeAccessable<T, RESULT_TYPE>;
