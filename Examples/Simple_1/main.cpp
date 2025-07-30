#include <vector>
#include "Examples/Main/Actions.hpp"
#include "Examples/Main/FillBackpack.hpp"
#include "Examples/Main/Print.hpp"

int main(int, [[maybe_unused]] char* argv[]) {
    // Redirect redirect{argv[0]};

    std::vector<Object> backpack;
    fillBackpack(backpack);

    backpack.push_back(living_weapon{Name{"Living_SWORD"}, Health{20}, Damage{20}});

    auto armorSet = ArmorSet{Name{"Body of Lidia"}};

    decltype(auto) armor_set_container = trait<WearContainer>::get(armorSet);

    armor_set_container.wearProtection(Protection{
        ArmorClass{5,
                   BodyLocation::Legs,
                   {EffectType::Burn, EffectType::Freeze}}});
    armor_set_container.wearProtection(Protection{
        ArmorClass{3,
                   BodyLocation::Arms,
                   {EffectType::Burn, EffectType::Freeze}}});

    backpack.push_back(armorSet);

    Object player(living_player{Name{"Knight"}, Health{100}});
    Object enemy(living_enemy{Name{"Ogr"}, Health{200}});
    Object enemy_2(Enemy{Name{"Ogr 2"}});

    print_person(player);
    print_person(enemy);
    print_person(enemy_2);
    std::cout << "\n";

    attack(backpack, player, enemy);
    defend(backpack, player);
    wear(backpack, player);
    enemy_defend(backpack, enemy);

    std::cout << Color::Red << "\nUse sleep scroll on player //////////////////////////////\n"
              << Color::Reset;
    Object sleep_scroll = scroll_3(
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}});
    sleep_scroll.doAction(Actions::Attack, &sleep_scroll, &player);
    print_person(player);
    std::cout << Color::Red << "//////////////////////////////\n\n"
              << Color::Reset;

    restore(backpack, player);
    heal(backpack, player);

    std::cout << Color::Red << "//////////////////////////////\n\n"
              << Color::Reset;

    std::cout << Color::Yellow << "print living items from backpack:\n"
              << Color::Reset;
    for (auto item = backpack.begin(); item != backpack.end(); ++item) {
        if (item->hasStrategyFor(Properties::Health)) {
            print_person(*item);
        }
    }
    std::cout << '\n';

    std::cout << Color::Yellow << "print protecting items from backpack:\n"
              << Color::Reset;
    for (auto item = backpack.begin(); item != backpack.end(); ++item) {
        if (item->hasStrategyFor(Properties::Protection)) {
            print_object(*item);
        }
    }
    std::cout << '\n';

    return 0;
}
