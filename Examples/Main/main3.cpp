#include <vector>
#include "Actions.hpp"
#include "FillBackpack.hpp"
#include "Object/Properties/UserProperty.hpp"
#include "Print.hpp"

int main() {
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
        /*dmg*/ std::ignore,       // can be ignored but not ommited if later is present
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
    }

    Object franco{gustav};

    print_object_properties(franco);
    std::cout << '\n';

    std::cout << "print franco:\n";
    print_object(franco);
    
    return 0;
}
