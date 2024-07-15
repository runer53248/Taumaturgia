#include <vector>
#include "Examples/Main/Print.hpp"

#ifdef WITH_ADD_PROPERTIES
#include "Examples/Main/structs_aP.hpp"
#else
#include "Examples/Main/structs_no_aP.hpp"
#endif

int main() {
    static_assert(Namingable<player_type>);
    static_assert(Livingable<player_type>);
    static_assert(Restoringable<player_type>);
    static_assert(Wearingable<player_type>);
    static_assert(is_alive_strategy<player_type>);
    static_assert(is_restore_strategy<player_type>);
    static_assert(is_wear_strategy<player_type>);

    // create player
    Object player = player_type{
        Name{"Player"},
        Health{100}};

    // player wear helmet protecting from stun
    defend(Object{
               Helmet{
                   Name{"VIKING_HELM"},
                   ArmorClass{2,
                              BodyLocation::Head,
                              {EffectType::Stun}}}},
           &player);

    print_person(player);

    Object stuning_log(Weapon{
        Name{"stuning Log"},
        Damage{6,
               Effect{
                   EffectType::Stun,
                   Duration{1, DurationType::Round}}}});

    Object freezing_log(Weapon{
        Name{"freezing log"},
        Damage{6,
               Effect{
                   EffectType::Freeze,
                   Duration{1, DurationType::Round}}}});

    std::cout << "attack with " << stuning_log.name() << '\n';
    attack(stuning_log, &player, &player);
    std::cout << "attack with " << freezing_log.name() << '\n';
    attack(freezing_log, &player);

    print_person(player);
    std::cout << '\n';

    auto weapon_a = Weapon{Name{"Weapon"}, Damage{6}};
    const auto weapon_b = Weapon{Name{"Weapon"}, Damage{6}};

    decltype(auto) damage_a = trait<Damage>::get(weapon_a);  // reference
    decltype(auto) damage_b = trait<Damage>::get(weapon_b);  // const reference

    static_assert(std::is_same_v<decltype(damage_a), Damage&>);
    static_assert(std::is_same_v<decltype(damage_b), const Damage&>);

    return 0;
}
