#pragma once
#include "Concepts/TypeConcepts.hpp"
#include "Helpers/trait_accessable.hpp"

#include "Structs/accessType.hpp"

template <typename T, typename RESULT_TYPE>
concept accessType_trait_able = trait_accessable<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_template_able = traits::GetTypeTemplateAccessable<T, RESULT_TYPE>;
