#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "Usage/Properties.hpp"

struct base {};

template <typename T>
using int_property = UserPropertyAdapter<int>::type<T>;

template <typename T>
using CureValueType_property = UserPropertyAdapter<CureValueType>::type<T>;

template <typename T>
using EffectContainer_property = UserPropertyAdapter<EffectContainer>::type<T>;

using CureHealthType = add_properties_ordered<
    base,
    int_property,
    CureValueType_property,
    EffectContainer_property>;

int main() {
    CureHealthType cureHealthType{5, CureValueType::CURRENT_PERCENT, EffectContainer{Effect{EffectType::Burn}, Effect{EffectType::Devour}}};

    std::cout << trait<int>::get(cureHealthType);
    std::cout << toString(trait<CureValueType>::get(cureHealthType));
    std::cout << trait<EffectContainer>::get(cureHealthType) << '\n';
}
