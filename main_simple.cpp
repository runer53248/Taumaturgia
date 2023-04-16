#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/DefaultStrategies.hpp"
#include "preety_print.hpp"
#include <vector>

/*actions 5
    attack
    defend
    heal
    restore
    get
*/

/*Enums 5
    BodyLocation
    DurationType
    EffectState
    EffectType
    Parameter
*/

/*types
    AC
        //enum BodyLocation
        //Effect
    Damage
        Effect
            Duration *
                //enum DurationType
            State *
                //enum EffectState
            //enum EffectType
    Hp
        EffectContainer *
    EffectTypeContainer * // aka RestoreList
    Name
    VariantType *
*/

/*parameters
    Hp
    CureHp
    Ac
    Damage
    Restore
*/

/*Properties
    Damaging
    Healing
    Living
    Naming
    Protecting
    Restoring
*/

struct Item {
    std::string name;
};

struct Weapon {
    std::string name;
};

struct Player{
    std::string name;
};

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon>{Name{"Sword"}, Damage{50, Effect{EffectType::Infection}}};
    Object weapon_2 = Damaging<Weapon>{Name{"Sword 2"}, Damage{50, Effect{EffectType::Stun}}};
    Object paladin( Living<Restoring<Player>>{Name{"Paladin"}, Hp{100}, EffectType::Infection} );

    container.push_back(Item{});

    auto print_hp = [](const auto& obj) {
        if (auto opt = getOpt<Parameter::Hp>(obj)) {
            const Hp& hp = opt.value();

            std::cout << "hp = " << hp.value();
            
            for (const auto& effect : hp.effects()) {
                std::cout << effect.effectType();

                if (effect.duration().type() == DurationType::Round) {
                    std::cout << " (" << effect.duration().value() << " rounds) ";
                }
                if (effect.duration().type() == DurationType::Instant) {
                    std::cout << " (" << effect.duration().value() << " instant) ";
                }
            }
            std::cout << '\n';
        }
    };

    print_hp(paladin);

    weapon.attack(&weapon, &paladin);
    print_hp(paladin);
    
    paladin.restore(&paladin);
    print_hp(paladin);

    weapon_2.attack(&weapon, &paladin);
    print_hp(paladin);
}
