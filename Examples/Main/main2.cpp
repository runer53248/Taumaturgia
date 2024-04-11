#include <vector>
#include "Actions.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
#include "Print.hpp"

#include "Examples/Structs/Helmet.hpp"
#include "Examples/Structs/Armor.hpp"

struct Empty {};

int main() {
    using all_properties_type = add_properties<
        Empty,
        Living,
        Wearing,
        Damaging,
        Protecting,
        Healing,
        Restoring,
        Naming>;

    Object obj = all_properties_type{
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

    Object{Helmet{
               Name{"VIKING_HELM"},
               ArmorClass{2,
                          BodyLocation::Head}}}
        .defend(&obj);
    Object{Armor{
               Name{"VIKING_Armor"},
               ArmorClass{8,
                          BodyLocation::Body,
                          {EffectType::Freeze, EffectType::Stun}}}}
        .defend(&obj);

    obj.defend(&obj);

    print_object(obj);

    print_protection(getOpt<Properties::Protection>(obj).value());
    std::cout << '\n';
    print_wear(getOpt<Properties::Wear>(obj).value());
    print_dmg(getOpt<Properties::Damage>(obj).value());
}
