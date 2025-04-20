#pragma once
#include "Taumaturgia/Strategies/Helpers/StrategyConditional.hpp"
#include "Usage/Types/Helpers/extract_optional_type.hpp"

template <typename T>
struct GetterStrategy_ {};

template <typename T>
concept is_custom_get_strategy = Strategable_template<GetterStrategy_, T, optional_get_variant_type, Properties>  //
                                 and Strategable_template<GetterStrategy_, const T, optional_get_variant_const_type, Properties>;

template <typename T>
using GetterStrategy = StrategyConditional<GetterStrategy_, T, Gettingable<T>, is_custom_get_strategy<T>>;
