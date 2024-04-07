#pragma once
#include "Taumaturgia/Traits/Helpers/trait_accessable.hpp"
#include "Taumaturgia/Traits/UserTypeTraits.hpp"

template <typename T, typename RESULT_TYPE>
concept getType_or_custom_accessable = trait_accessable<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_able = traits::GetTypeAccessable<T, RESULT_TYPE>;
