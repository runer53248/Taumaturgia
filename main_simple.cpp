#include "Object/Object.hpp"
#include "Object/Properties/Properties.hpp"
#include "Object/DefaultStrategies.hpp"
#include <vector>
#include <iostream>

/*actions
    attack
    defend
    heal
    restore
    get
*/

/*Enums
    BodyLocation
    DurationType
    EffectState
    EffectType
*/

/*types
    AC
    Damage
    Duration *
    Effect
    Hp
    Name
    State *
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

struct Player{};

int main() {
    std::vector<Object> container;

    Object weapon = Damaging<Weapon>{Name{"Sword"}, Damage{50, Effect{EffectType::Infection}}};
    Object paladin( Living<Restoring<Naming<Player>>>{Name{"Paladin"}, Hp{100}, EffectTypeContainer{EffectType::Infection} } );

    container.push_back(Item{});

    auto print_hp = [](auto& obj) {
        if (auto opt_variant = get(obj, Parameter::Hp)) {
            const auto& hp = Get<Hp>(opt_variant.value());

            std::cout << "hp = " << hp.value();
            
            for (const auto& effect : hp.effects()) {
                switch(effect.effectType()){
                    case EffectType::Infection:
                        std::cout << " [Infection]";
                        break;
                    case EffectType::None:
                        std::cout << " [none]";
                        break;
                    default:
                        std::cout << " [unknown]";
                        break;
                }
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

    
}
