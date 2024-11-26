#include "Examples/PreetyPrint/preety_print.hpp"
#include "Examples/basic_strategies.hpp"
#include "Examples/demangle_type_name.hpp"

// MARK: Weapon_A

struct Weapon_A {
    std::string name;
    Damage dmg;
};

// MARK: Weapon_B

class Weapon_B {
public:
    std::string name;

    Weapon_B(const std::string& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    auto& getDamage() { return dmg; }
    const auto& getDamage() const { return dmg; }

private:
    Damage dmg;
};

// MARK: Weapon_C

class Weapon_C {
public:
    Name name;

    Weapon_C(const Name& name, Damage dmg)
        : name{name}, dmg{dmg} {}

    constexpr auto& Dmg() { return dmg; }
    constexpr const auto& Dmg() const { return dmg; }

private:
    Damage dmg;
};

// MARK: Weapon_D

struct Empty {};
using Weapon_D = add_properties_ordered<
    Empty,
    Naming,
    Damaging>;

// MARK: Weapon_C Damage

template <typename T>
    requires std::is_base_of_v<Weapon_C, T>
struct traits::CustomAccessType<Damage, T> {
    static constexpr decltype(auto) get(auto& el) {
        return el.Dmg();
    }
};

// MARK: attack_impl_x

inline constexpr ActionStatus attack_impl_x(Damagingable auto& obj, Object* owner, Object*) {
    std::cout << "X owner name: " << owner->name() << "   " << trait<Damage>::get(obj) << '\n';
    return {};
}

// MARK: UserStrategy_<Damage, Weapon_D, ...>
// MARK: AttackStrategy_<Weapon_D>

template <>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Damage, Weapon_D> {  // override UserStrategy_<T, Default, ActionStatus>
#else
struct AttackStrategy_<Weapon_D> {  // override AttackStrategy_<Default>
#endif
    static constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object*) {
        return attack_impl_x(obj, owner, nullptr);
    }
};

// MARK: attack_impl

inline constexpr ActionStatus attack_impl(Damagingable auto& obj, Object* owner, Object*) {
    std::cout << "owner name: " << owner->name() << "   " << trait<Damage>::get(obj) << '\n';
    return {};
}

// MARK: UserStrategy_<Damage, Damagingable>
// MARK: AttackStrategy_<Damagingable>

template <Damagingable T>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Damage, T> {
#else
struct AttackStrategy_<T> {
#endif
    static constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object*) {
        return attack_impl(obj, owner, nullptr);
    }
};

// MARK: main

int main(int, char** argv) {
    static_assert(Damagingable<Weapon_A>);
    static_assert(Damagingable<Weapon_B>);
    static_assert(Damagingable<Weapon_C>);
    static_assert(Damagingable<Weapon_D>);

    auto default_damage = Damage{50,
                                 Effect{
                                     EffectType::Stun,
                                     Duration{5, DurationType::Round},
                                     EffectState::Active}};

    Object weapon_a = Weapon_A{Name{"Sword A"}, default_damage};
    Object weapon_b = Weapon_B{Name{"Sword B"}, default_damage};
    Object weapon_c = Weapon_C{Name{"Sword C"}, default_damage};
    Object weapon_d = Weapon_D{Name{"Sword D"}, default_damage};

    std::cout << "weapon attack:\n";

    attack(weapon_a, &weapon_a);
    // print_object_properties(weapon_a);
    print_object(weapon_a);

    attack(weapon_b, &weapon_b);
    // print_object_properties(weapon_b);
    print_object(weapon_b);

    attack(weapon_c, &weapon_c);
    // print_object_properties(weapon_c);
    print_object(weapon_c);

    attack(weapon_d, &weapon_d);
    // print_object_properties(weapon_d);
    print_object(weapon_d);
    std::cout << "\n";

    std::cout << "Weapon_A = " << name<Weapon_A>() << "\n";
    std::cout << "Weapon_B = " << name<Weapon_B>() << "\n";
    std::cout << "Weapon_C = " << name<Weapon_C>() << "\n";
    std::cout << "Weapon_D = " << name<Weapon_D>() << "\n";
    std::cout << "\n";
    std::cout << "trait<Damage> = " << name<trait<Damage>>() << "\n";
    std::cout << "trait<Name> = " << name<trait<Name>>() << "\n";
    std::cout << "program = " << argv[0] << "\n"
              << "\n";
}
