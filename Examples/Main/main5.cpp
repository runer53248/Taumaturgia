#include <vector>
#include "Actions.hpp"
#include "FillBackpack.hpp"
#include "Object/Properties/UserProperty.hpp"
#include "Print.hpp"

int main() {
    Object player(living_player{Name{"Knight"}, Health{100}});
    Object enemy(living_enemy{Name{"Ogr"}, Health{200}});
    Object enemy_2(Enemy{Name{"Ogr 2"}});
    Object log(Weapon{Name{"Log"}, Damage{6, Effect{EffectType::Stun, Duration{1, DurationType::Round}}}});
    Object npc(named_npc{Name{"Npc"}});

    print_person(player);
    print_person(enemy);
    print_person(enemy_2);

    std::cout << "\nenemy_2 attack player with Stunning " << log.name() << ":\n\n";
    log.attack(&enemy_2, &player);

    print_person(player);
    std::cout << '\n';

    print_person(enemy);
    std::cout << '\n';

    std::cout << "\nprint player and enemies:\n\n";
    print_person(player);
    print_person(enemy);
    print_person(enemy_2);  // enemy_2 dont have hp

    print_person(npc);
    std::cout << '\n';

    std::cout << "\nprint npc after healing:\n\n";
    using healing_potion = potion_1;
    Object{healing_potion{Name{"HEALING_POTION"}, CureHealth{100}}}
        .heal(&npc);
    print_person(npc);
    std::cout << '\n';

    std::cout << "\nprint npc after stun restoration:\n\n";
    Object{restoring_potion{Name{"Stun restore potion"}, {EffectType::Stun, EffectType::Daze}}}
        .restore(&npc);
    print_person(npc);
    std::cout << '\n';

    print_person(enemy);
    std::cout << "\nprint devoured enemy after stun restoration:\n\n";
    Object{restoring_potion{Name{"Stun restore potion"}, {EffectType::Stun, EffectType::Daze}}}
        .restore(&enemy);
    print_person(enemy);
    std::cout << '\n';

    std::cout << "print potion restore effects:\n";

    Object restore_potion{restoring_potion{
        Name{"Multi restore potion"},
        {EffectType::Stun,
         EffectType::Daze,
         EffectType::Infection,
         EffectType::Poison}}};

    getOpt<Parameter::Restore>(restore_potion)
        .and_then(print_restore)
        .and_then(print_new_line);
    std::cout << '\n';

    print_object_properties(restore_potion);
    print_object_properties(player);
    std::cout << '\n';

    getOpt<Parameter::Health>(player)
        .and_then([](Health& hp) {
            std::cout << "player hp = " << hp.value() << '\n';
            constexpr auto new_hp = 100;
            hp.value(new_hp);
            std::cout << "player hp change to  " << hp.value() << '\n';
            return std::optional{hp};
        });

    getOpt<Parameter::Health, const Object>(player)
        .and_then([](const Health& hp) { return std::optional{hp}; });
    getOpt<Parameter::Health, const Object>(player)
        .and_then([](auto hp_ref_wrap) {
            const Health& hp = hp_ref_wrap.get();
            std::cout << "player hp = " << hp.value() << '\n';
            return std::optional{hp_ref_wrap};
        });
    std::cout << '\n';

    const Object potion{healing_potion{
        Name{"HEALING_POTION"},
        CureHealth{75}}};

    getOpt<Parameter::CureHealth>(potion)
        .and_then([](const CureHealth& cure) {
            std::cout << "potion heal = " << cure << '\n';
            return std::optional{cure};
        });

    return 0;
}
