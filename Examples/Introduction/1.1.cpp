#include "../../Object/Properties/Properties.hpp"

struct EmptyType {};

struct Type_living {
    Name name;
    Health hp;
};

using Type_named = Naming<EmptyType>;

using Type_1 = Living<Type_named>;
using Type_2 = add_properties<Type_named, Living>;
using Type_2a = add_properties<EmptyType, Naming, Living>;
using Type_2b = add_properties<EmptyType, Living, Naming>;

static_assert(std::is_same_v<Type_1, Type_2>);
static_assert(sizeof(Type_living) == sizeof(Type_2));
static_assert(sizeof(Type_living) == sizeof(Type_2a));
static_assert(sizeof(Type_living) == sizeof(Type_2b));
static_assert(std::is_same_v<Type_2a, Type_2b>);

struct Type_all {
    Name name;
    Health hp;
    ProtectionContainer armorWear;
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
using Type_4 = add_properties<EmptyType,
                              Naming,
                              Living,
                              Wearing,
                              Damaging,
                              Protecting,
                              Healing,
                              Restoring>;
using Type_5 = add_properties<Type_named,
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

#include "../../Examples/preety_print_types.hpp"

int main() {
    Type_living type0{Name{"Valid"}, Health{50}};
    Type_1 type1{Name{"Valid"}, Health{50}};
    Type_2 type2{Name{"Valid"}, Health{50}};

    Type_all typeAll{Name{"Valid"}, Health{}, ProtectionContainer{}, Damage{}, Protection{}, CureHealth{}, EffectTypeContainer{}};

    // Type_3, Type_4 and Type_5 are the same type
    Type_3 type3_0{};                                                                                                             // all properties defaulted
    Type_3 type3{Name{"Valid"}, Health{50}};                                                                                      // rest of properties defaulted by not mention them
    Type_4 type4{Name{"Valid"}, std::ignore, std::ignore, std::ignore, std::ignore, CureHealth{25}, std::ignore};                 // ignore some of properties
    Type_5 type5{Name{"Valid"}, Health{25}, ProtectionContainer{}, Damage{}, Protection{}, CureHealth{}, EffectTypeContainer{}};  // set all properties
    std::cout << "type3_0 Name:       " << type3_0.getName() << '\n';
    std::cout << "type3 Hp:           " << type3.getHp() << '\n';
    std::cout << "type4 CureHp:       " << type4.getCureHealth() << '\n';
    std::cout << "type5 Hp:           " << type5.getHp() << '\n';
    std::cout << '\n';

    type5.getArmorWear().wearProtection(Protection{ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}}});
    type5.getArmorWear().wearProtection(Protection{ArmorClass{4, BodyLocation::Arms, {EffectType::Burn}}});
    type5.getArmorWear().wearProtection(Protection{ArmorClass{5, BodyLocation::Legs, {EffectType::Burn, EffectType::Freeze}}});

    type5.getDamage() = Damage{15, DamageType::Physical, Effect{EffectType::Poison, Duration{5, DurationType::Round}, State{EffectState::Inactive}}};
    type5.getProtection() = ArmorClass{8, BodyLocation::Body, {EffectType::Paralyze}};
    type5.getCureHealth() = CureHealth{15, {Effect{EffectType::Devour}, Effect{EffectType::Shock}}};
    type5.getRestoreEffects() = {EffectType::Burn, EffectType::Smite};

    std::cout << "Name:         " << type5.getName() << '\n';
    std::cout << "Hp:           " << type5.getHp() << '\n';
    std::cout << "Armor:        " << type5.getArmorWear() << '\n';
    std::cout << "Damage:       " << type5.getDamage() << '\n';
    std::cout << "Protection:   " << type5.getProtection() << '\n';
    std::cout << "CureHp:       " << type5.getCureHealth() << '\n';
    std::cout << "Restore:      " << type5.getRestoreEffects() << '\n';

    return 0;
}
