#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

struct Potion {
    Name name;
};

struct ProtectPotion {
    Name name;
    Protection protection{};
};

struct Healty {
    Name name;
    Health hp{};
};

int main() {
    Protecting<Damaging<Potion>>{
        Name{"SHIELD_POTION"},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Damage{10}};
    Damaging<Protecting<Potion>>{
        Name{"SHIELD_POTION"},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Damaging<Protecting<ProtectPotion>>{
        Name{"SHIELD_POTION"},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Damaging<Protecting<Potion>>{
        Name{"SHIELD_POTION"},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Living<ProtectPotion>{
        Name{"SHIELD_POTION"},
        Health{},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Living<Damaging<ProtectPotion>>{
        Name{"SHIELD_POTION"},
        Health{},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Living<Potion>{
        Name{"SHIELD_POTION"},
        Health{}};

    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-value"
    Living<Healty>{
        Name{"SHIELD_POTION"},
        Health{}};  // Living ignored - c-tor of Healty used
    #pragma clang diagnostic pop
    #else
    Living<Healty>{
        Name{"SHIELD_POTION"},
        Health{}};  // Living ignored - c-tor of Healty used
    #endif

    Living<Potion>{
        Name{"SHIELD_POTION"},
        Health{}};  // Living used - c-tor of Living can't be used

    Living<Potion>{
        Name{"SHIELD_POTION"},
        std::ignore};

    Living<Damaging<Protecting<Potion>>>{
        Name{"SHIELD_POTION"},
        Health{},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Damaging<Living<Protecting<Potion>>>{
        Name{"SHIELD_POTION"},
        Damage{10},
        Health{},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Protecting<Damaging<Living<Potion>>>{
        Name{"SHIELD_POTION"},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Damage{10},
        Health{}};
    Living<Protecting<Damaging<Potion>>>{
        Name{"SHIELD_POTION"},
        Health{},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Damage{10}};
    Protecting<Living<Damaging<Potion>>>{
        Name{"SHIELD_POTION"},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Health{},
        Damage{10}};
    Damaging<Protecting<Living<Potion>>>{
        Name{"SHIELD_POTION"},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Health{}};

    Restoring<Damaging<Protecting<Potion>>>{
        Name{"SHIELD_POTION"},
        EffectTypeContainer{},
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Health health{5};
    CureHealth cureHealth{10};
    Damage damage{10};
    EffectTypeContainer effectTypeContainer{};
    ArmorClass armorClass{4, BodyLocation::Internal, {EffectType::Sleep}};
    ProtectionContainer protectionContainer{};

    Healing<Living<Restoring<Damaging<Protecting<Wearing<Potion>>>>>>{
        Name{"SHIELD_POTION"},
        cureHealth,
        health,
        effectTypeContainer,
        damage,
        armorClass,
        protectionContainer};

    Living<Restoring<Damaging<Protecting<Potion>>>>{
        Name{"SHIELD_POTION"},
        Health{},
        EffectType::Contagion,  // single EffectType
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Living<Restoring<Damaging<Protecting<Potion>>>>{
        Name{"SHIELD_POTION"},
        Health{},
        EffectTypeContainer{EffectType::Contagion, EffectType::Devour, EffectType::Slow},  // multiple EffectType
        Damage{10},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Protecting<Potion>{
        Name{"SHIELD_POTION"},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    ArmorClass ac{4, BodyLocation::Internal, {EffectType::Sleep}};
    Protecting<Potion>{
        Name{"SHIELD_POTION"},
        ac};

    Damaging<Potion>{
        Name{"SHIELD_POTION"},
        Damage{10}};
}
