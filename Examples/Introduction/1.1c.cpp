#include "Examples/Checks.hpp"
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Usage/Properties.hpp"

struct EmptyType {};

using Type_5 = add_properties_ordered<
    EmptyType,
    Naming,
    Healing,
    Protecting,
    Restoring,
    Living,
    Wearing,
    Damaging>;

int main() {
    Type_5 type4{Name{"Valid"},
                 Health{25},
                 WearContainer{},
                 Damage{},
                 Protection{},
                 CureHealth{},
                 EffectTypeContainer{}};  // set all properties

    trait<WearContainer>::get(type4).wearProtection(
        Protection{ArmorClass{
            8,
            BodyLocation::Body,
            {EffectType::Paralyze}}});

    trait<WearContainer>::get(type4).wearProtection(
        Protection{ArmorClass{
            4,
            BodyLocation::Arms,
            {EffectType::Burn}}});

    trait<WearContainer>::get(type4).wearProtection(
        Protection{ArmorClass{
            5,
            BodyLocation::Legs,
            {EffectType::Burn, EffectType::Freeze}}});

    trait<Damage>::get(type4) = Damage{
        15,
        DamageType::Physical,
        Effect{EffectType::Poison, Duration{5, DurationType::Round}, EffectState::Inactive}};

    trait<Protection>::get(type4) = ArmorClass{
        8,
        BodyLocation::Body,
        {EffectType::Paralyze}};

    trait<CureHealth>::get(type4) = CureHealth{
        15,
        {Effect{EffectType::Devour}, Effect{EffectType::Shock}}};
    trait<EffectTypeContainer>::get(type4) = {EffectType::Burn, EffectType::Smite};

    std::cout << "Name:         " << trait<Name>::get(type4) << '\n';
    std::cout << "Hp:           " << trait<Health>::get(type4) << '\n';
    std::cout << "Armor:        " << trait<WearContainer>::get(type4) << '\n';
    std::cout << "Damage:       " << trait<Damage>::get(type4) << '\n';
    std::cout << "Protection:   " << trait<Protection>::get(type4) << '\n';
    std::cout << "CureHp:       " << trait<CureHealth>::get(type4) << '\n';
    std::cout << "Restore:      " << trait<EffectTypeContainer>::get(type4) << '\n';
    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
