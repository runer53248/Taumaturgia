#include <vector>
#include "Actions.hpp"
#include "Examples/Checks.hpp"
#include "Print.hpp"

#include "Examples/Structs/Armor.hpp"
#include "Examples/Structs/Helmet.hpp"

struct Empty {};

int main() {
    using type_with_all_buildin_properties = add_properties_ordered<
        Empty,
        Living,
        Wearing,
        Damaging,
        Protecting,
        Healing,
        Restoring,
        Naming>;

    Object obj = type_with_all_buildin_properties{
        Name("ultimate"),
        Health{24},
        WearContainer{10},
        Damage{
            10,
            Effect{EffectType::Burn}},
        ArmorClass{
            5,
            BodyLocation::Legs,
            {EffectType::Slow}},
        CureHealth{15, {Effect{EffectType::Devour}, Effect{EffectType::Shock}}},
        EffectTypeContainer{EffectType::Sleep}};

    defend(
        Object{Helmet{
            Name{"VIKING_HELM"},
            ArmorClass{2,
                       BodyLocation::Head}}},
        &obj);
    defend(
        Object{Armor{
            Name{"VIKING_Armor"},
            ArmorClass{8,
                       BodyLocation::Body,
                       {EffectType::Freeze, EffectType::Stun}}}},
        &obj);

    defend(
        obj,
        &obj);

    print_object(obj);

    getOpt<Properties::Protection>(obj)
        .and_then(print_protection)
        .and_then(print_new_line)
        .and_then(print_new_line);

    getOpt<Properties::Damage>(obj)
        .and_then(print_dmg)
        .and_then(print_new_line)
        .and_then(print_new_line);

    getOpt<Properties::Wear>(obj)
        .and_then(print_wear)
        .and_then(print_new_line);

        {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
