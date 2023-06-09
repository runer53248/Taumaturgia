#include <vector>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Examples/preety_print.hpp"

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
    Protecting<Damaging<Potion>>{Name{"SHIELD_POTION"}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Damage{10}};
    Damaging<Protecting<Potion>>{Name{"SHIELD_POTION"}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Protecting<Damaging<Potion>>{Name{"SHIELD_POTION"}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Damage{10}};

    Damaging<ProtectPotion>{Name{"SHIELD_POTION"}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Damaging<Protecting<Potion>>{Name{"SHIELD_POTION"}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Living<ProtectPotion>{Name{"SHIELD_POTION"}, Health{}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Living<Damaging<ProtectPotion>>{Name{"SHIELD_POTION"}, Health{}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Living<Potion>{Name{"SHIELD_POTION"}, Health{}};
    // Living<Potion>{Name{"SHIELD_POTION"}, 1};

    Living<Healty>{Name{"SHIELD_POTION"}, Health{}};
    // Living<Healty>{Name{"SHIELD_POTION"}, 1};

    Living<Damaging<Protecting<Potion>>>{Name{"SHIELD_POTION"}, Health{}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Damaging<Living<Protecting<Potion>>>{Name{"SHIELD_POTION"}, Damage{10}, Health{}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};
    Protecting<Damaging<Living<Potion>>>{Name{"SHIELD_POTION"}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Damage{10}, Health{}};

    Living<Protecting<Damaging<Potion>>>{Name{"SHIELD_POTION"}, Health{}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Damage{10}};
    Protecting<Living<Damaging<Potion>>>{Name{"SHIELD_POTION"}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Health{}, Damage{10}};
    Damaging<Protecting<Living<Potion>>>{Name{"SHIELD_POTION"}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Health{}};
    Damaging<Protecting<Living<Potion>>>{Name{"SHIELD_POTION"}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Health{}};

    Living<Protecting<Damaging<Potion>>>{Name{"SHIELD_POTION"}, Health{}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}, Damage{10}};

    Living<Restoring<Damaging<Protecting<Potion>>>>{Name{"SHIELD_POTION"}, Health{}, EffectTypeContainer{}, Damage{10}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    Protecting<Potion>{Name{"SHIELD_POTION"}, ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    ArmorClass ac{4, BodyLocation::Internal, {EffectType::Sleep}};
    ArmorClass ac2{4, BodyLocation::Internal, {EffectType::Sleep}};
    Protecting<Potion>{Name{"SHIELD_POTION"}, ac};

    Damaging<Potion>{Name{"SHIELD_POTION"}, Damage{10}};
}
