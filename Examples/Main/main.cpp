#include <vector>

#include "Examples/preety_print.hpp"
#include "Examples/structs.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

#include "Actions.hpp"
#include "FillBackpack.hpp"
#include "Print.hpp"

void simple() {
    Object player(Living<Player>{
        Name{"Player"},
        Health{100}});

    Object{
        Helmet{
            Name{"VIKING_HELM"},
            ArmorClass{
                2,
                BodyLocation::Head,
                {EffectType::Stun}}}}
        .defend(&player);

    print_person(player);

    Object log(Weapon{
        Name{"Log"},
        Damage{
            6,
            Effect{
                EffectType::Stun,
                Duration{1, DurationType::Round}}}});

    Object log_2(Weapon{
        Name{"Log 2"},
        Damage{
            6,
            Effect{
                EffectType::Freeze,
                Duration{1, DurationType::Round}}}});

    std::cout << "attack with Stunning " << log.name() << " (have protection):\n";
    log.attack(&log, &player);
    print_person(player);

    std::cout << "attack with Freezing " << log_2.name() << " (don't have protection):\n";
    log_2.attack(&log_2, &player);
    print_person(player);
    std::cout << '\n';

    auto weapon_2 = Weapon{Name{"Weapon"}, Damage{6}};
    decltype(auto) val_2 = traits::accessDamage::get(weapon_2);  // reference
    static_assert(std::is_same_v<decltype(val_2), Damage&>);

    const auto weapon_3 = Weapon{Name{"Weapon"}, Damage{6}};
    decltype(auto) val_3 = traits::accessDamage::get(weapon_3);  // const reference
    static_assert(std::is_same_v<decltype(val_3), const Damage&>);
}

int main() {
    simple();

    // TODO: require order of Properties to remove similiar types with different order
    std::vector<Object> backpack;
    fillBackpack(backpack);

    auto gustav = Living<Healing<Living<Healing<Weapon>>>>{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*healHp*/ CureHealth{}};  // duplicated Living and Healing will be ignored
    static_assert(std::is_same_v<decltype(gustav), Living<Healing<Weapon>>>);
    // gustav.name = Name{"Franco The Inteligent Sword"};
    // gustav.hp = Health{75}; // can't be accessed now - is private
    // gustav.getHp() = Health{75}; // current access version
    traits::accessName::get(gustav) = Name{"Franco The Inteligent Sword"};
    traits::accessHealth::get(gustav) = Health{75};  // universal access version
    traits::accessCureHealth::get(gustav) = CureHealth{30};
    traits::accessDamage::get(gustav) = Damage{
        100,
        DamageType::Magical,
        Effect{
            EffectType::Stun,
            Duration{3, DurationType::Round},
            State{EffectState::Active}}};

    Object gustav_obj{gustav};
    std::cout << '\n'
              << gustav_obj.name() << '\n';
    get_print_const_ref(gustav_obj);
    std::cout << '\n';
    get_print_ref(gustav_obj);
    std::cout << '\n';
    get_print_with_damage_as_const(gustav_obj);
    std::cout << '\n';
    backpack.push_back(std::move(gustav_obj));

    backpack.push_back(Living<Weapon>{
        Name{"Living_SWORD"},
        Health{20},
        Damage{20}});

    Object player(Living<Player>{
        Name{"Knight"},
        Health{100}});
    Object enemy(Living<Enemy>{
        Name{"Ogr"},
        Health{200}});
    Object enemy_2(Enemy{
        Name{"Ogr 2"}});
    print_person(player);
    print_person(enemy);
    print_person(enemy_2);
    std::cout << "\n";

    Object scroll = Damaging<Scroll>{
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}}};
    scroll.attack(&player);
    std::cout << "attack player with SLEEP_SCROLL\n";
    print_object(scroll);

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    Object burn = Damaging<Scroll>{
        Name{"Burn_scroll"},
        Damage{
            0,
            Effect{EffectType::Burn}}};
    burn.attack(&player);
    std::cout << "attack player with Burn_scroll\n";
    print_object(burn);

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    attack(backpack, player, enemy);

    defend(backpack, player);

    enemy_defend(backpack, enemy);

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    restore(backpack, player);

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    heal(backpack, player);

    std::cout << "//////////////////////////////\n\n";

    print_person(player);
    Object log(Weapon{
        Name{"Log"},
        Damage{
            6,
            Effect{
                EffectType::Stun,
                Duration{1, DurationType::Round}}}});
    std::cout << "attack with Stunning " << log.name() << " (have protection):\n";
    log.attack(&enemy_2, &player);
    print_person(player);
    std::cout << '\n';

    print_person(enemy);

    Object franco{gustav};
    // std::cout << "attack with " << franco.name() << ":\n";
    // franco.attack(&franco, &enemy);
    // print_person(enemy);
    // std::cout << '\n';

    Object npc(Naming<Npc>{
        Name{"Npc"}});
    std::cout << "defend with " << franco.name() << ":\n";
    franco.defend(&npc);  // npc can't defend with franco - ignored
    std::cout << '\n';

    print_person(npc);
    std::cout << "attack self with " << franco.name() << ":\n";
    franco.attack(&npc);  // npc hit himself with franco
    print_person(npc);
    std::cout << '\n';

    std::cout << "print player and enemies:\n";
    print_person(player);
    print_person(enemy);
    print_person(enemy_2);  // enemy_2 dont have hp
    std::cout << '\n';

    print_person(npc);
    std::cout << "print npc after healing:\n";
    Object{Healing<Potion>{
               Name{"HEALING_POTION"},
               CureHealth{100}}}
        .heal(&npc);
    print_person(npc);
    std::cout << '\n';

    print_person(npc);
    std::cout << "print npc after stun restoration:\n";
    Object{Restoring<Potion>{
               Name{"Stun restore potion"},
               {EffectType::Stun, EffectType::Daze}}}
        .restore(&npc);
    print_person(npc);
    std::cout << '\n';

    print_person(enemy);
    std::cout << "print devoured enemy after stun restoration:\n";
    Object{Restoring<Potion>{
               Name{"Stun restore potion"},
               {EffectType::Stun, EffectType::Daze}}}
        .restore(&enemy);
    print_person(enemy);
    std::cout << '\n';

    std::cout << "print living items in backpack:\n";
    for (auto item = backpack.begin(); item != backpack.end(); ++item) {
        if (item->can_alive) {
            print_person(*item);
        }
    }
    std::cout << '\n';

    std::cout << "print potion restore effects:\n";
    Object restore_potion{Restoring<Potion>{
        Name{"Multi restore potion"},
        {EffectType::Stun,
         EffectType::Daze,
         EffectType::Infection,
         EffectType::Poison}}};
    getOpt<Parameter::Restore>(restore_potion)
        .and_then(print_restore)
        .and_then(print_new_line);
    std::cout << "\n";

    print_object_properties(restore_potion);
    print_object_properties(player);
    print_object_properties(franco);
    std::cout << '\n';

    std::cout << "print franco:\n";
    print_object(franco);
    std::cout << '\n';

    getOpt<Parameter::Health>(player)
        .and_then([](Health& hp) {
            std::cout << "player hp = " << hp.value() << '\n';
            constexpr auto new_hp = 100;
            hp.value(new_hp);
            std::cout << "player hp change to  " << hp.value() << '\n';
            return std::optional<bool>(true);
        });
    getOpt<Parameter::Health>(player)
        .and_then([](auto hp_ref_wrap) {
            Health& hp = hp_ref_wrap.get();
            std::cout << "player hp = " << hp.value() << '\n';
            return std::optional<bool>(true);
        });
    std::cout << '\n';

    const Object potion{Healing<Potion>{
        Name{"HEALING_POTION"},
        CureHealth{75}}};

    getOpt<Parameter::CureHealth>(potion)
        .and_then([](const CureHealth& cure) {
            std::cout << "potion heal = " << cure.value() << toString(cure.valueType()) << '\n';
            return std::optional<bool>(true);
        });

    return 0;
}
