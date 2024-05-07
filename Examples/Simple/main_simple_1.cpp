#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Taumaturgia/Properties/Properties.hpp"

// MARK: Weapon_A

struct Weapon_A {
    std::string name;
    Damage dmg;
};

#ifdef WITH_ADD_PROPERTIES
template <typename T>
    requires std::is_base_of_v<Weapon_A, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.dmg);
    }
};
#endif

// MARK: Weapon_B

class Weapon_B {
public:
    std::string name;

    Weapon_B(std::string name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& getDamage() { return dmg; }
    const auto& getDamage() const { return dmg; }

private:
    Damage dmg;
};

#ifdef WITH_ADD_PROPERTIES
template <typename T>
    requires std::is_base_of_v<Weapon_B, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.getDamage();
    }
};
#endif

class Weapon_C {
public:
    std::string name;

    Weapon_C(const std::string& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& Dmg() { return dmg; }
    const auto& Dmg() const { return dmg; }

private:
    Damage dmg;
};

// MARK: CustomAccessDamage<Weapon_C>

#ifndef WITH_ADD_PROPERTIES
template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessDamage<T> {
#else
template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessType<Damage, T> {
#endif
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

// MARK: Weapon_D

struct Default {};
struct Empty {};
using Weapon_D = add_properties<Empty, Naming, Damaging>;

#ifdef WITH_ADD_PROPERTIES
// override struct UserStrategy_<T, Default, ActionStatus> from basic_strategies
template <>
struct UserStrategy_<Damage, Default, ActionStatus> {
    constexpr ActionStatus operator()(auto& obj, Object* owner, Object*) const {
        std::cout << "X owner name: " << owner->name() << "   " << Damagingable_trait::get(obj) << '\n';
        return ActionStatus::Success;
    }
};
#endif

// MARK: attack strategy

template <Damagingable T>
#ifndef NO_PREMADE_STRATEGIES
struct AttackStrategy_<T> {
#else
struct UserStrategy_<Damage, T, ActionStatus> {
#endif
    constexpr ActionStatus operator()([[maybe_unused]] Damagingable auto& obj, Object* owner, Object*) const {
        std::cout << "owner name: " << owner->name() << "   " << Damagingable_trait::get(obj) << '\n';
        return {};
    }
};

// MARK: main

int main() {
    std::vector<Object> container;

    static_assert(Damagingable<Weapon_A>);
    static_assert(Damagingable<Weapon_B>);
    static_assert(Damagingable<Weapon_C>);
    static_assert(Damagingable<Weapon_D>);

    Object weapon_a = Weapon_A{
        Name{"Sword A"},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   EffectState::Active}}};

    Object weapon_b = Weapon_B{
        Name{"Sword B"},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   EffectState::Active}}};

    Object weapon_c = Weapon_C{
        Name{"Sword C"},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   EffectState::Active}}};

    Object weapon_d = Weapon_D{
        Name{"Sword D"},
        Damage{50,
               Effect{
                   EffectType::Stun,
                   Duration{5, DurationType::Round},
                   EffectState::Active}}};

    std::cout << "weapon attack:\n";

    attack(weapon_a, &weapon_a);
    print_object_properties(weapon_a);
    print_object(weapon_a);

    attack(weapon_b, &weapon_b);
    print_object_properties(weapon_b);
    print_object(weapon_b);

    attack(weapon_c, &weapon_c);
    print_object_properties(weapon_c);
    print_object(weapon_c);

    attack(weapon_d, &weapon_d);
    print_object_properties(weapon_d);
    print_object(weapon_d);
    std::cout << "\n";
}
