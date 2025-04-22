#include <vector>
#include "Actions.hpp"
#include "FillBackpack.hpp"
#include "Print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

int main() {
    using gustav_weapon = add_properties_ordered<
        Weapon,
        Living,
        Healing,
        Living,
        Healing>;
    static_assert(std::is_same_v<
                  gustav_weapon,
                  add_properties_ordered<
                      Weapon,
                      Living,
                      Healing>>);

#ifdef WITH_ADD_PROPERTIES
    std::cout << "example: with add_properties\n";

    auto gustav = gustav_weapon{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ std::ignore,       // can be ignored but not ommited if later is present
        /*healHp*/ CureHealth{}};  // can be ommited
#else
    std::cout << "example: classic\n";

    auto gustav = gustav_weapon{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*healHp*/ CureHealth{},
        /*dmg*/ Damage{}};  // can be ommited - type inside Weapon type
#endif

    // universal access by trait
    trait<Name>::get(gustav) = Name{"Franco The Inteligent Sword"};
    trait<Health>::get(gustav) = Health{75};
    trait<CureHealth>::get(gustav) = CureHealth{30};
    trait<Damage>::get(gustav) = Damage{100,
                                        DamageType::Magical,
                                        Effect{
                                            EffectType::Stun,
                                            Duration{3, DurationType::Round},
                                            EffectState::Active}};
    {
        Object gustav_obj{gustav};

        std::cout << '\n';
        std::cout << gustav_obj.name() << '\n';
        getOpt_print(gustav_obj);
        std::cout << '\n';
    }

    print_properties(gustav);
    print_object(gustav);

    return 0;
}
