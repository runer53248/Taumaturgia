#include <iostream>
#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

struct Potion {
    Name name;
};

int main() {
    const Name spiked_shield_potion_name{"Spiked Shield Potion"};
    const auto restore_effect_initializer = {EffectType::Sleep, EffectType::Sleep};
    const auto protecting_effect_initializer = {EffectType::Sleep};
    constexpr Effect damage_effect{EffectType::Bleed};
    constexpr auto armor_value{4};
    constexpr auto armor_location{BodyLocation::Internal};
    constexpr auto damage_value{10};

    using restoring_protecting_damaging_potion = Restoring<Protecting<Damaging<Potion>>>;

    // constructor: all properties set
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore_effect_initializer,                                              // restoring
        ArmorClass{armor_value, armor_location, protecting_effect_initializer},  // protecting
        Damage{damage_value, damage_effect}};                                    // damaging

    // constructor: all properties set from tuples
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::tuple(restore_effect_initializer),                                  // restoring
        std::tuple(armor_value, armor_location, protecting_effect_initializer),  // protecting
        std::tuple(damage_value, damage_effect)};                                // damaging

    // constructor: ignoring first 2 properties
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                           // restoring
        std::ignore,                           // protecting
        Damage{damage_value, damage_effect}};  // damaging

    // constructor: last property set from tuple
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                               // restoring
        std::ignore,                               // protecting
        std::tuple{damage_value, damage_effect}};  // damaging

    // constructor: first property set
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore_effect_initializer};  // restoring

    // constructor: all properties default
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name};

    // constructor: incorect tuple to set property
    try {
        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            std::ignore,
            std::ignore,
            std::make_tuple("test")};  // restoring
    } catch (const std::logic_error& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    EffectTypeContainer restore{restore_effect_initializer};
    Protection protection{ArmorClass{armor_value, armor_location, protecting_effect_initializer}};
    Damage damage{damage_value, damage_effect};

    using container = std::variant<std::monostate, Damage, Protection, EffectTypeContainer>;

    // constructor: properties set from variants
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        container{restore},     // restoring
        container{protection},  // protecting
        container{damage}};     // damaging

    std::variant<std::monostate, Damage> damage_variant{damage};

    // constructor: properties set if correct variant given
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        damage_variant,   // restoring
        damage_variant,   // protecting
        damage_variant};  // damaging
}
