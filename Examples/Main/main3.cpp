#include <print>
#include <vector>
#include "Actions.hpp"
#include "Examples/Checks.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"
#include "structs.hpp"

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
    std::println("example: with add_properties");

    auto gustav = gustav_weapon{
        Name{"GUSTAV_INTELIGENT_SWORD"},
        /*hp*/ Health{20},
        /*dmg*/ std::ignore,       // can be ignored but not ommited if later is present
        /*healHp*/ CureHealth{}};  // can be ommited
#else
    std::println("example: classic");

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

        std::println();
        std::println("{}", gustav_obj.name());
        getOpt_print(gustav_obj);
        std::println();
    }

    {
        print_properties(gustav);
        print_object(gustav);

        std::println("---------------------");
        std::println("type gustav_weapon:");
        std::println("{}", parse_type_name<gustav_weapon>());
        std::println("builded from type Weapon:");
        std::println("{}", parse_type_name<Weapon>());

        using my_armor = add_properties_ordered<Armor, Living>;

        std::println("---------------------");
        std::println("type my_armor:");
        std::println("{}", parse_type_name<my_armor>());
        std::println("builded from type Armor:");
        std::println("{}", parse_type_name<Armor>());

        using my_potion = add_properties_ordered<Potion, Living>;

        std::println("---------------------");
        std::println("type my_potion:");
        std::println("{}", parse_type_name<my_potion>());
        std::println("builded from type Potion:");
        std::println("{}", parse_type_name<Potion>());

        using my_scroll = add_properties_ordered<Scroll, Living>;

        std::println("---------------------");
        std::println("type my_scroll:");
        std::println("{}", parse_type_name<my_scroll>());
        std::println("builded from type Scroll:");
        std::println("{}", parse_type_name<Scroll>());

        using my_player = add_properties_ordered<Player, Living>;

        std::println("---------------------");
        std::println("type my_player:");
        std::println("{}", parse_type_name<my_player>());
        std::println("builded from type Player:");
        std::println("{}", parse_type_name<Player>());

        my_player player{Name{"Player"}};

        // static_assert(have_getType_type_method<my_player, Data<WearContainer, Player_tag>>);

        std::println("{}", getType<2>(player));
        std::println("{}", player.getType<WearContainer>());
        std::println("{}", getTypeTaged<WearContainer, Player_tag>(player));
    }

    {
#ifdef USES_ADD_PROPERTIES
        check_aP<true>();
#else
        check_aP<false>();
#endif
    }
}
