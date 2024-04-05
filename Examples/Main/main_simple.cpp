#include <vector>
#include "Print.hpp"
#include "structs.hpp"

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
    Object{
        Helmet{
            Name{"VIKING_HELM"},
            ArmorClass{2,
                       BodyLocation::Head,
                       {EffectType::Stun}}}}
        .defend(&player);

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
    stuning_log.attack(&player, &player);
    std::cout << "attack with " << freezing_log.name() << '\n';
    freezing_log.attack(&player);

    print_person(player);
    std::cout << '\n';

    auto weapon_2 = Weapon{Name{"Weapon"}, Damage{6}};
    const auto weapon_3 = Weapon{Name{"Weapon"}, Damage{6}};

    decltype(auto) damage_2 = traits::accessDamage::get(weapon_2);  // reference
    decltype(auto) damage_3 = traits::accessDamage::get(weapon_3);  // const reference

    static_assert(std::is_same_v<decltype(damage_2), Damage&>);
    static_assert(std::is_same_v<decltype(damage_3), const Damage&>);

    return 0;
}
