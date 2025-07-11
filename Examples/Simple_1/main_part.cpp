#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct base {};

template <typename T>
using int_property = UserPropertyAdapter<int>::once<T>;

template <typename T>
using CureValueType_property = UserPropertyAdapter<CureValueType>::once<T>;

template <typename T>
using EffectContainer_property = UserPropertyAdapter<EffectContainer>::once<T>;

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
