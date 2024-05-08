#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct base {};

#ifdef WITH_ADD_PROPERTIES
template <typename T>
    using int_property = UserPropertyAdapter<int>::type<T>;
    template <typename T>
    using CureValueType_property = UserPropertyAdapter<CureValueType>::type<T>;
    template <typename T>
    using EffectContainer_property = UserPropertyAdapter<EffectContainer>::type<T>;

    using CureHealthType = add_properties<
        base,
        int_property,
        CureValueType_property,
        EffectContainer_property>;
#else
    using CureHealthType = UserProperty<
        int,
        UserProperty<CureValueType,
                    UserProperty<EffectContainer,
                                base>>>;

#endif

int main() {
    CureHealthType cureHealthType{5, CureValueType::CURRENT_PERCENT, EffectContainer{Effect{EffectType::Burn}, Effect{EffectType::Devour}}};

    std::cout << traits::accessType<int>::get(cureHealthType);
    std::cout << toString(traits::accessType<CureValueType>::get(cureHealthType));
    std::cout << traits::accessType<EffectContainer>::get(cureHealthType) << '\n';
}
