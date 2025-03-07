#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Usage/Properties.hpp"

#include <functional>

struct EmptyType {};

struct Type_living {
    Name name;
    Health hp;
};

using Type_named = Naming<EmptyType>;

using Type_1 = Living<Type_named>;
using Type_2 = add_properties_ordered<
    Type_named,
    Living>;
using Type_2a = add_properties_ordered<
    EmptyType,
    Naming,
    Living>;
using Type_2b = add_properties_ordered<
    EmptyType,
    Living,
    Naming>;

static_assert(std::is_same_v<Type_1, Type_2>);
static_assert(sizeof(Type_living) == sizeof(Type_2));
static_assert(sizeof(Type_living) == sizeof(Type_2a));
static_assert(sizeof(Type_living) == sizeof(Type_2b));
static_assert(std::is_same_v<Type_2a, Type_2b>);

struct Type_all {
    Name name;
    Health hp;
    WearContainer armorWear;
    Damage dmg;
    Protection protection;
    CureHealth cureHealth;
    EffectTypeContainer restoreEffects;
};
static_assert(Namingable<Type_all>);
static_assert(Livingable<Type_all>);
static_assert(Protectingable<Type_all>);
static_assert(Damagingable<Type_all>);
static_assert(Wearingable<Type_all>);
static_assert(Healingable<Type_all>);
static_assert(Restoringable<Type_all>);

using Type_3 = Living<Wearing<Damaging<Protecting<Healing<Restoring<Naming<EmptyType>>>>>>>;
using Type_4 = add_properties_ordered<
    EmptyType,
    Naming,
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring>;
using Type_5 = add_properties_ordered<
    Type_named,
    Healing,
    Protecting,
    Restoring,
    Living,
    Wearing,
    Damaging>;

// Type_3, Type_4 and Type_5 are the same type
static_assert(std::is_same_v<Type_3, Type_4>);
static_assert(std::is_same_v<Type_4, Type_5>);
// Type_all passing all properties concepts have same size as empty type with all properties given
static_assert(sizeof(Type_all) == sizeof(Type_5));

int main() {
    Type_living type0{Name{"Valid"}, Health{50}};
    Type_1 type1{Name{"Valid"}, Health{50}};
    Type_2 type2{Name{"Valid"}, Health{50}};

    Type_all typeAll{Name{"Valid"}, Health{}, WearContainer{}, Damage{}, Protection{}, CureHealth{}, EffectTypeContainer{}};

    // Type_3, Type_4 and Type_5 are the same type
    Type_3 type3_0{};                                                                                                       // all properties defaulted
    Type_3 type3{Name{"Valid"}, Health{50}};                                                                                // rest of properties defaulted by not mention them
    Type_4 type4{Name{"Valid"}, std::ignore, std::ignore, std::ignore, std::ignore, CureHealth{25}, std::ignore};           // ignore some of properties
    Type_5 type5{Name{"Valid"}, Health{25}, WearContainer{}, Damage{}, Protection{}, CureHealth{}, EffectTypeContainer{}};  // set all properties
    using health_tuple = std::tuple<int, EffectContainer>;                                                                  // types used in Health C-tor
    using protectionContainer_tuple = std::tuple<int>;                                                                      // types used in WearContainer C-tor
    using cureHealth_tuple = std::tuple<int, CureValueType>;                                                                // types used in CureHealth C-tor
    Type_5 type5_1{Name{"Valid"},                                                                                           // create properties from tuples
                   health_tuple{25, {Effect{EffectType::Burn}, Effect{EffectType::Freeze}}},
                   protectionContainer_tuple{10},
                   Damage{},
                   std::ignore,
                   cureHealth_tuple{10, CureValueType::MAX_PERCENT},
                   EffectTypeContainer{}};
    using variant_type_1 = std::variant<Health, WearContainer, Damage, Protection, CureHealth, EffectTypeContainer>;
    using variant_type_2 = std::variant<Damage>;
    variant_type_2 varDmg = Damage{120, DamageType::Divine};
    std::vector<variant_type_1> vec{Health{125}, WearContainer{}, Damage{20, DamageType::Magical}, Protection{}, CureHealth{}, EffectTypeContainer{}};
    Type_5 type5_2{Name{"Valid"}, vec[0], vec[1], vec[2], vec[3], vec[4], vec[5]};  // create properties from variants
    Type_5 type5_3{Name{"Valid"}, varDmg, varDmg, varDmg};                          // create properties from wrong variants

#ifndef NO_PREMADE_PROPERTIES
    std::cout << "type3_0 Name:       " << type3_0.getName() << '\n';
    std::cout << "type3 Hp:           " << type3.getHealth() << '\n';
    std::cout << "type4 CureHp:       " << type4.getCureHealth() << '\n';
    std::cout << "type5 Hp:           " << type5.getHealth() << '\n';
    std::cout << "type5_1 Hp:         " << type5_1.getHealth() << '\n';
    std::cout << "type5_1 Armor:      " << type5_1.getArmorWear() << '\n';
    std::cout << "type5_1 CureHp:     " << type5_1.getCureHealth() << '\n';
    std::cout << "type5_2 Hp:         " << type5_2.getHealth() << '\n';
    std::cout << "type5_2 Damage:     " << type5_2.getDamage() << '\n';
    std::cout << "type5_3 Damage:     " << type5_3.getDamage() << '\n';
    std::cout << '\n';
#else
    std::cout << "type3_0 Name:       " << type3_0.getType<Name>() << '\n';
    std::cout << "type3 Hp:           " << type3.getType<Health>() << '\n';
    std::cout << "type4 CureHp:       " << type4.getType<CureHealth>() << '\n';
    std::cout << "type5 Hp:           " << type5.getType<Health>() << '\n';
    std::cout << "type5_1 Hp:         " << type5_1.getType<Health>() << '\n';
    std::cout << "type5_1 Armor:      " << type5_1.getType<WearContainer>() << '\n';
    std::cout << "type5_1 CureHp:     " << type5_1.getType<CureHealth>() << '\n';
    std::cout << "type5_2 Hp:         " << type5_2.getType<Health>() << '\n';
    std::cout << "type5_2 Damage:     " << type5_2.getType<Damage>() << '\n';
    std::cout << "type5_3 Damage:     " << type5_3.getType<Damage>() << '\n';
    std::cout << '\n';
#endif

#ifndef NO_PREMADE_PROPERTIES
    type5.getArmorWear().wearProtection(Protection{ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}}});
    type5.getArmorWear().wearProtection(Protection{ArmorClass{4, BodyLocation::Arms, {EffectType::Burn}}});
    type5.getArmorWear().wearProtection(Protection{ArmorClass{5, BodyLocation::Legs, {EffectType::Burn, EffectType::Freeze}}});

    type5.getDamage() = Damage{15, DamageType::Physical, Effect{EffectType::Poison, Duration{5, DurationType::Round}, EffectState::Inactive}};
    type5.getProtection() = ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}};
    type5.getCureHealth() = CureHealth{15, {Effect{EffectType::Devour}, Effect{EffectType::Shock}}};
    type5.getRestoreEffects() = {EffectType::Burn, EffectType::Smite};
#else
    type5.getType<WearContainer>().wearProtection(Protection{ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}}});
    type5.getType<WearContainer>().wearProtection(Protection{ArmorClass{4, BodyLocation::Arms, {EffectType::Burn}}});
    type5.getType<WearContainer>().wearProtection(Protection{ArmorClass{5, BodyLocation::Legs, {EffectType::Burn, EffectType::Freeze}}});

    type5.getType<Damage>() = Damage{15, DamageType::Physical, Effect{EffectType::Poison, Duration{5, DurationType::Round}, EffectState::Inactive}};
    type5.getType<Protection>() = ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}};
    type5.getType<CureHealth>() = CureHealth{15, {Effect{EffectType::Devour}, Effect{EffectType::Shock}}};
    type5.getType<EffectTypeContainer>() = {EffectType::Burn, EffectType::Smite};
#endif

#ifndef NO_PREMADE_PROPERTIES
    std::cout << "Name:         " << type5.getName() << '\n';
    std::cout << "Hp:           " << type5.getHealth() << '\n';
    std::cout << "Armor:        " << type5.getArmorWear() << '\n';
    std::cout << "Damage:       " << type5.getDamage() << '\n';
    std::cout << "Protection:   " << type5.getProtection() << '\n';
    std::cout << "CureHp:       " << type5.getCureHealth() << '\n';
    std::cout << "Restore:      " << type5.getRestoreEffects() << '\n';
#else
    std::cout << "Name:         " << type5.getType<Name>() << '\n';
    std::cout << "Hp:           " << type5.getType<Health>() << '\n';
    std::cout << "Armor:        " << type5.getType<WearContainer>() << '\n';
    std::cout << "Damage:       " << type5.getType<Damage>() << '\n';
    std::cout << "Protection:   " << type5.getType<Protection>() << '\n';
    std::cout << "CureHp:       " << type5.getType<CureHealth>() << '\n';
    std::cout << "Restore:      " << type5.getType<EffectTypeContainer>() << '\n';
#endif

    return 0;
}
