#include <vector>
#include "Actions.hpp"
#include "Examples/Checks.hpp"
#include "FillBackpack.hpp"
#include "Print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

int main() {
    std::vector<Object> backpack;
    fillBackpack(backpack);

    backpack.push_back(living_weapon{Name{"Living_SWORD"}, Health{20}, Damage{20}});

    Object player(living_player{Name{"Knight"}, Health{100}});
    Object enemy(living_enemy{Name{"Ogr"}, Health{200}});
    Object enemy_2(Enemy{Name{"Ogr 2"}});

    print_person(player);
    print_person(enemy);
    print_person(enemy_2);
    std::cout << "\n";

    using damaging_scroll = scroll_3;
    Object scroll = damaging_scroll{Name{"SLEEP_SCROLL"}, Damage{0, Effect{EffectType::Sleep}}};
    std::cout << "attack player with SLEEP_SCROLL\n";
    attack(
        scroll,
        &player);
    print_object(scroll);
    std::cout << "player info\n";
    print_object(player);

    Object burn = damaging_scroll{Name{"Burn_scroll"}, Damage{0, Effect{EffectType::Burn}}};
    std::cout << "attack player with Burn_scroll\n";
    attack(
        burn,
        &player);
    print_object(burn);
    std::cout << "player info\n";
    print_object(player);

    {
#ifdef USES_ADD_PROPERTIES
       check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
