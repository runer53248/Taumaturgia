#include <vector>
#include "Actions.hpp"
#include "FillBackpack.hpp"
#include "Object/Properties/UserProperty.hpp"
#include "Print.hpp"

int main() {
    std::vector<Object> backpack;

    fillBackpack(backpack);

#ifdef WITH_ADD_PROPERTIES
    std::cout << "*** WITH_ADD_PROPERTIES ***" << '\n';

    using gustav_weapon = add_properties<Weapon, Living, Healing, Living, Healing>;
    static_assert(std::is_same_v<gustav_weapon, add_properties<Weapon, Living, Healing>>);

    static_assert(std::is_same_v<
                  gustav_weapon,
                  Living<Damaging<Healing<Naming<Type>>>>>);  // Type is base from with Weapon is build
    // static_assert(std::is_same_v<gustav_weapon, Living<Damaging<Healing<Naming<Weapon>>>>>); // ! old way will not reorder Damaging property from build Weapon type

    auto gustav = gustav_weapon{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ std::ignore,       // must be ignored but not ommited if later is present
        /*healHp*/ CureHealth{}};  // can be ommited
#else
    std::cout << "*** WITHOUT_ADD_PROPERTIES ***" << '\n';

    using gustav_weapon = Living<Healing<Living<Healing<Weapon>>>>;
    static_assert(std::is_same_v<gustav_weapon, Living<Healing<Weapon>>>);

    static_assert(std::is_same_v<
                  gustav_weapon,
                  Living<Healing<Damaging<Naming<Weapon>>>>>);

    auto gustav = gustav_weapon{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*healHp*/ CureHealth{},
        /*dmg*/ Damage{}};  // can be ommited - type inside Weapon type
#endif

    traits::accessName::get(gustav) = Name{"Franco The Inteligent Sword"};
    traits::accessHealth::get(gustav) = Health{75};  // universal access version
    traits::accessCureHealth::get(gustav) = CureHealth{30};
    traits::accessDamage::get(gustav) = Damage{100,
                                               DamageType::Magical,
                                               Effect{
                                                   EffectType::Stun,
                                                   Duration{3, DurationType::Round},
                                                   State{EffectState::Active}}};

    {
        Object gustav_obj{gustav};

        std::cout << '\n';
        std::cout << gustav_obj.name() << '\n';
        get_print_const_ref(gustav_obj);
        std::cout << '\n';
        get_print_ref(gustav_obj);
        std::cout << '\n';
        get_print_with_damage_as_const(gustav_obj);
        std::cout << '\n';
        backpack.push_back(std::move(gustav_obj));
    }

    backpack.push_back(living_weapon{
        Name{"Living_SWORD"},
        Health{20},
        Damage{20}});

    Object player(living_player{
        Name{"Knight"},
        Health{100}});
    Object enemy(living_enemy{
        Name{"Ogr"},
        Health{200}});
    Object enemy_2(Enemy{
        Name{"Ogr 2"}});
    print_person(player);
    print_person(enemy);
    print_person(enemy_2);
    std::cout << "\n";

    using damaging_scroll = scroll_3;

    Object scroll = damaging_scroll{
        Name{"SLEEP_SCROLL"},
        Damage{
            0,
            Effect{EffectType::Sleep}}};
    scroll.attack(&player);
    std::cout << "attack player with SLEEP_SCROLL\n";
    print_object(scroll);

    std::cout << "Current player:  //////////////////////////////\n\n";
    print_object(player);

    Object burn = damaging_scroll{
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

    Object npc(named_npc{
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

    using healing_potion = potion_1;

    print_person(npc);
    std::cout << "print npc after healing:\n";
    Object{healing_potion{
               Name{"HEALING_POTION"},
               CureHealth{100}}}
        .heal(&npc);
    print_person(npc);
    std::cout << '\n';

    print_person(npc);
    std::cout << "print npc after stun restoration:\n";
    Object{restoring_potion{
               Name{"Stun restore potion"},
               {EffectType::Stun, EffectType::Daze}}}
        .restore(&npc);
    print_person(npc);
    std::cout << '\n';

    print_person(enemy);
    std::cout << "print devoured enemy after stun restoration:\n";
    Object{restoring_potion{
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
    Object restore_potion{restoring_potion{
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
            return std::optional{hp};
        });
    getOpt<Parameter::Health>(player)
        .and_then([](auto hp_ref_wrap) {
            Health& hp = hp_ref_wrap.get();
            std::cout << "player hp = " << hp.value() << '\n';
            return std::optional{hp_ref_wrap};
        });
    std::cout << '\n';

    const Object potion{healing_potion{
        Name{"HEALING_POTION"},
        CureHealth{75}}};

    getOpt<Parameter::CureHealth>(potion)
        .and_then([](const CureHealth& cure) {
            std::cout << "potion heal = " << cure.value() << toString(cure.valueType()) << '\n';
            return std::optional{cure};
        });

    return 0;
}
