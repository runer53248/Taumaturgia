#include <vector>
#include "Object/DefaultStrategies.hpp"
#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"

#include "Examples/preety_print.hpp"
#include "Examples/structs.hpp"

int main() {
    std::vector<Object> backpack;

    backpack.emplace_back(Damaging<Weapon>{
        Name{"SWORD"},
        Damage{16}});
    backpack.emplace_back(Weapon{
        Name{"GIANT_SWORD"},
        Damage{32}});
    backpack.emplace_back(CustomWeapon{
        Name{"Custom_SWORD"}});
    backpack.emplace_back(Damaging<CustomWeapon>{
        Name{"New_Custom_SWORD"},
        Damage{32}});  // became Damagingable - custom AttackStrategy_<CustomWeapon> from 'struct.hpp'will handle it
    backpack.emplace_back(Damaging<DefaultWeapon>{
        Name{"Default_BATTLE_SWORD"},
        Damage{32}});

    auto gustav = Living<Healing<Living<Healing<Weapon>>>>{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*healHp*/ Health{}};  // duplicated Living and Healing will be ignored
    static_assert(std::is_same_v<decltype(gustav), Living<Healing<Weapon>>>);
    gustav.name = Name{"Franco The Inteligent Sword"};
    traits::accessHealth::get(gustav) = Health{75};
    traits::accessCureHealth::get(gustav) = Health{30};
    gustav.dmg = Damage{100,
                        Effect{
                            EffectType::Stun,
                            Duration{3, DurationType::Round},
                            State{EffectState::Active}}};
    Object gustav_obj{gustav};

    std::cout << '\n'
              << gustav_obj.name() << '\n';
    std::cout << "get and print by lambda taking const reference:\n";
    [](const auto& obj) {  // get version passing const reference
        getOpt<Parameter::Health>(obj)
            .and_then(print_hp);
        std::cout << '\n';
        getOpt<Parameter::CureHealth>(obj)
            .and_then(print_cure_hp);
        std::cout << '\n';
        // getOpt<Parameter::Protection>(obj)
        //    .and_then(print_protection); // ignored - object dont have Ac
        // std::cout << '\n';
        getOpt<Parameter::Damage>(obj)
            .and_then(print_dmg);
        std::cout << '\n';
    }(gustav_obj);

    std::cout << '\n';
    std::cout << "get and print by lambda taking reference:\n";  // non-const object will return optional to non-const reference wraper - printing will then show [&]
    [](auto& obj) {                                              // get version passing reference
        getOpt<Parameter::Health>(obj)
            .and_then(print_hp);
        std::cout << '\n';
        getOpt<Parameter::CureHealth>(obj)
            .and_then(print_cure_hp);
        std::cout << '\n';
        // getOpt<Parameter::Protection>(obj).and_then(print_protection); // ignored - object dont have Ac
        // std::cout << '\n';
        getOpt<Parameter::Damage>(obj)
            .and_then(print_dmg);
        std::cout << '\n';
    }(gustav_obj);

    std::cout << '\n';
    std::cout << "get and print:\n";
    getOpt<Parameter::Health>(gustav_obj)
        .and_then(print_hp);  // get version passing reference
    std::cout << '\n';
    getOpt<Parameter::CureHealth>(gustav_obj)
        .and_then(print_cure_hp);
    std::cout << '\n';
    // getOpt<Parameter::Protection>(gustav_obj).and_then(print_protection); // ignored - object dont have Ac
    // std::cout << '\n';
    std::cout << "get and print - forced to return const reference:\n";
    getOpt<Parameter::Damage, const Object>(gustav_obj)
        .and_then(print_dmg);  // force get version passing const reference
    std::cout << '\n';
    std::cout << '\n';

    backpack.push_back(std::move(gustav_obj));

    // arguments in constructor are from left to right - same as added properties (only Naming requires to be most right as all properties need to be used on Namingable type)
    auto gustav_2 = Living<Healing<Living<Healing<Weapon>>>>(
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ Health{30},
        Damage{32});
    Living<Healing<Living<Healing<Naming<NoNameWeapon>>>>>(
        Name{"INCOGNITO SWORD"},
        /*hp*/ Health{20},
        /*cureHealth*/ Health{30},
        Damage{32});
    static_assert(std::is_same_v<decltype(gustav_2), Living<Healing<Weapon>>>);
    backpack.emplace_back(gustav_2);

    backpack.emplace_back(Armor{
        Name{"CHAIN_MAIL"},
        Protection{
            8,
            BodyLocation::Body}});
    backpack.emplace_back(Protecting<Armor>{
        Name{"HALF_PLATE"},
        Protection{
            ArmorClass{12}}});

    backpack.emplace_back(Damaging<Helmet>{
        Name{"BATTLE_HELM"},
        Damage{10},
        ArmorClass{
            4,
            BodyLocation::Head,
            {EffectType::Daze}}});
    backpack.emplace_back(Helmet{
        Name{"VIKING_HELM"},
        ArmorClass{
            2,
            BodyLocation::Head,
            {EffectType::Stun}}});
    backpack.emplace_back(Healing<Potion>(
        Name{"HEALING_POTION"},
        Health{20}));
    backpack.emplace_back(Healing<Potion>{
        Name{"SMALL_HEALING_POTION"},
        Health{10}});  // TODO: add removing effects
    backpack.emplace_back(Protecting<Potion>(
        Name{"SHIELD_POTION"},
        ArmorClass{
            4,
            BodyLocation::Internal,
            {EffectType::Sleep}}));
    backpack.emplace_back(Scroll{
        Name{"USELESS_SCROLL"}});
    backpack.emplace_back(Scroll{
        Name{"EMPTY_SCROLL"}});
    backpack.emplace_back(Restoring<Scroll>{
        Name{"AWAKE_SCROLL"},
        {EffectType::Sleep}});
    backpack.emplace_back(Damaging<Scroll>(
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}}));
    backpack.emplace_back(Damaging<Healing<Scroll>>(
        Name{"VAMPIRIC_TOUCH_SCROLL"},
        Damage{
            30,
            Effect{EffectType::Devour}},
        Health{15}));

    Object player(Living<Player>{
        Name{"Knight"},
        Health{100}});
    Object enemy(Living<Enemy>{
        Name{"Ogr"},
        Health{180}});
    Object enemy_2(Enemy{
        Name{"Ogr 2"}});
    print_person(player);
    print_person(enemy);
    print_person(enemy_2);
    std::cout << "\n\n";

    Object{Damaging<Scroll>{
               Name{"SLEEP_SCROLL"},
               Damage{
                   0,
                   Effect{EffectType::Sleep}}}}
        .attack(&player);

    std::cout << "Items I can attack with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_attack) {
            continue;
        }
        std::cout << player.name() << " attack " << enemy.name() << " with " << item.name();
        getOpt<Parameter::Damage>(item)
            .and_then(print_dmg);
        std::cout << '\n';
        if (not item.attack(&player, &enemy)) {
            std::cout << " attack miss ";  // unusable yet
        }
        print_person(enemy);
    }
    std::cout << '\n';

    std::cout << "Items I can defend with:  //////////////////////////////\n";
    std::cout << "(armor protection don't restore ongoing effect - need to use correct restore or have both restore and living properties as target of attack)\n\n";
    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        if (not item.defend(&player /*, &player*/)) {
            std::cout << " protection broken\n";  // when target dont have Wearingable property
            std::cout << player.name() << " can't defend self with " << item.name();
            std::cout << '\n';
            continue;
        }

        std::cout << player.name() << " defend self with " << item.name();
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection);
        std::cout << '\n';
        print_person(player);
    }
    std::cout << '\n';

    std::cout << "Items enemy try defend with:  //////////////////////////////\n";
    std::cout << "(enemy don't have wearingable property)\n\n";

    for (const auto& item : backpack) {
        if (not item.can_defend) {
            continue;
        }
        if (not item.defend(&enemy /*, &player*/)) {
            std::cout << " protection broken\n";  // when target dont have Wearingable property
            std::cout << enemy.name() << " can't defend self with " << item.name();
            std::cout << '\n';
            continue;
        }

        std::cout << enemy.name() << " defend self with " << item.name();
        getOpt<Parameter::Protection>(item)
            .and_then(print_protection);
        std::cout << '\n';
        print_person(enemy);
    }
    std::cout << '\n';

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    std::cout << "Items I can restore with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_restore) {
            continue;
        }
        if (not item.restore(&player, &player)) {
            std::cout << " restoration don't work ";  // unusable yet
        }

        std::cout << player.name() << " restore self with " << item.name();
        // get(item, Parameter::Restore).and_then(print_restore);
        getOpt<Parameter::Restore>(item)
            .and_then(print_restore);  // same
        std::cout << '\n';
        print_person(player);
    }
    std::cout << '\n';

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    std::cout << "Items I can heal with:  //////////////////////////////\n\n";
    for (const auto& item : backpack) {
        if (not item.can_heal) {
            continue;
        }
        if (not item.heal(&player, &player)) {
            std::cout << " healing don't work ";  // unusable yet
        }

        std::cout << player.name() << " heal self with " << item.name();
        if (auto cureHealth_opt = getOpt<Parameter::CureHealth>(item)) {
            const Health& cureHealth = cureHealth_opt.value();
            std::cout << " for " << cureHealth.value() << " Health";
        }
        std::cout << '\n';
        print_person(player);
    }
    std::cout << "\n//////////////////////////////\n\n";

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
               Health{100}}}
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
        .and_then(print_restore);
    std::cout << "\n\n";

    print_object_properties(restore_potion);
    print_object_properties(player);
    print_object_properties(franco);
    std::cout << '\n';

    print_object(franco);
    std::cout << '\n';

    getOpt<Parameter::Health>(player)
        .and_then([](Health& hp) {
            std::cout << hp.value() << '\n';
            hp.value(100);
            return std::optional<bool>(true);
        });
    getOpt<Parameter::Health>(player)
        .and_then([](auto hp_ref_wrap) {
            std::cout << hp_ref_wrap.get().value() << '\n';
            return std::optional<bool>(true);
        });

    const Object potion{Healing<Potion>{
        Name{"HEALING_POTION"},
        Health{75}}};
    getOpt<Parameter::CureHealth>(potion)
        .and_then([](const Health cure) {
            std::cout << cure.value() << '\n';
            return std::optional<bool>(true);
        });

    return 0;
}
