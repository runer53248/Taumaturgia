#pragma once
#include "Helpers/traits_helper.hpp"
#include "Structs/accessType.hpp"

template <typename T, typename RESULT_TYPE>
concept accessType_trait_able = traits::helpers::trait_accessable<T, traits::accessType<RESULT_TYPE>, RESULT_TYPE>;

template <typename T, typename RESULT_TYPE>
concept getType_template_able = traits::GetTypeTemplateAccessable<T, RESULT_TYPE>;
