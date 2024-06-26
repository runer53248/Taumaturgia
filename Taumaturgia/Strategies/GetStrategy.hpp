#pragma once
#include <concepts>
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Usage/Types/Helpers/extract_optional_type.hpp"

template <typename T>
struct GetStrategy_ {};

template <typename T>
concept is_custom_get_strategy = Strategable_template<GetStrategy_, T, optional_get_variant_type, Properties>  //
                                 and Strategable_template<GetStrategy_, const T, optional_get_variant_const_type, Properties>;

template <typename T>
using GetStrategy = StrategyConditional<GetStrategy_, T, Gettingable<T>, is_custom_get_strategy<T>>;
