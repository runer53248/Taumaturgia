#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/Properties.hpp"
// #include "Taumaturgia/Strategies/DefaultStrategies.hpp"
#include "Examples/basic_strategies.hpp"

// MARK: Weapon_A

struct Weapon_A {
    std::string name;
    Damage dmg;
};

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

// MARK: Weapon_C

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

template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessDamage<T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

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

    std::cout << "weapon attack:\n";
    attack(weapon_a, &weapon_a);
    attack(weapon_b, &weapon_b);
    attack(weapon_c, &weapon_c);
    std::cout << "\n";

    print_object_properties(weapon_a);
    print_object(weapon_a);
    print_object_properties(weapon_b);
    print_object(weapon_b);
    print_object_properties(weapon_c);
    print_object(weapon_c);
}
