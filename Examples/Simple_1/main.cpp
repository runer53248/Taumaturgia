#include <vector>
#include "Examples/Main/Actions.hpp"
#include "Examples/Main/FillBackpack.hpp"
#include "Examples/Main/Print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

int main(int, [[maybe_unused]] char* argv[]) {
    // Redirect redirect{argv[0]};

    std::vector<Object> backpack;
    fillBackpack(backpack);

    backpack.push_back(living_weapon{Name{"Living_SWORD"}, Health{20}, Damage{20}});

    auto armorSet = ArmorSet{Name{"Body of Lidia"}};

    trait<WearContainer>::get(armorSet).wearProtection(Protection{
        ArmorClass{5, BodyLocation::Legs, {EffectType::Burn, EffectType::Freeze}}});
    trait<WearContainer>::get(armorSet).wearProtection(Protection{
        ArmorClass{3, BodyLocation::Arms, {EffectType::Burn, EffectType::Freeze}}});

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
    restore(backpack, player);
    heal(backpack, player);

    std::cout << "//////////////////////////////\n\n";

    std::cout << "print living items from backpack:\n";
    for (auto item = backpack.begin(); item != backpack.end(); ++item) {
        if (item->hasProperty(Properties::Health)) {
            print_person(*item);
        }
    }
    std::cout << '\n';

    return 0;
}
