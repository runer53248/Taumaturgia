#include <iostream>
#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

struct Potion {
    Name name;
};

constinit Effect damage_effect{EffectType::Bleed};
constinit auto armor_value{4};
constinit auto armor_location{BodyLocation::Internal};
constinit auto damage_value{10};

int main() {  // TODO: implement test based on this example
    const Name spiked_shield_potion_name{"Spiked Shield Potion"};
    const auto restore_effect_initializer = {EffectType::Sleep, EffectType::Sleep};
    const auto protecting_effect_initializer = {EffectType::Sleep};

    EffectTypeContainer restore{restore_effect_initializer};
    Protection protection{ArmorClass{armor_value, armor_location, protecting_effect_initializer}};
    Damage damage{damage_value, damage_effect};

    const EffectTypeContainer const_restore{restore_effect_initializer};
    const Protection const_protection{ArmorClass{armor_value, armor_location, protecting_effect_initializer}};
    const Damage const_damage{damage_value, damage_effect};

    using restoring_protecting_damaging_potion = Restoring<Protecting<Damaging<Potion>>>;

    // constructor: all properties set from reference
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore,     // restoring
        protection,  // protecting
        damage};     // damaging

    // constructor: all properties set from const reference
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        const_restore,     // restoring
        const_protection,  // protecting
        const_damage};     // damaging

    // constructor: all properties set from move types or initializer_list
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

    std::tuple restoring_tuple(restore_effect_initializer);
    std::tuple protecting_tuple(armor_value, armor_location, protecting_effect_initializer);
    std::tuple damaging_tuple(damage_value, damage_effect);

    // constructor: all properties set from tuples
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restoring_tuple,   // restoring
        protecting_tuple,  // protecting
        damaging_tuple};   // damaging

    // constructor: last property set from tuple by reference
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,  // restoring
        std::ignore,  // protecting
        damage};      // damaging

    // constructor: last property set from tuple by move
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                           // restoring
        std::ignore,                           // protecting
        Damage{damage_value, damage_effect}};  // damaging

    // constructor: last property set from tuple by reference
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,      // restoring
        std::ignore,      // protecting
        damaging_tuple};  // damaging

    // constructor: last property set from tuple by move
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

    // constructor: incorrect tuple to set property
    try {
        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            std::tuple{"test"},
            std::ignore,
            std::tuple{"test"}};  // damaging
    } catch (const std::logic_error& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    // constructor: incorrect tuple to set property
    try {
        std::tuple tuple_invalid_for_restoring{"test"};
        std::tuple tuple_invalid_for_damaging{"test"};

        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            tuple_invalid_for_restoring,
            std::ignore,
            tuple_invalid_for_damaging};  // damaging
    } catch (const std::logic_error& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    // constructor: incorrect tuple to set property
    try {
        std::tuple tuple_invalid_for_restoring{"test"};
        std::tuple tuple_invalid_for_damaging{"test"};

        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            std::move(tuple_invalid_for_restoring),
            std::ignore,
            std::move(tuple_invalid_for_damaging)};  // damaging
    } catch (const std::logic_error& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    using container = std::variant<std::monostate, Damage, Protection, EffectTypeContainer>;

    // constructor: properties set from moved types or initializer_list
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        {restore_effect_initializer},                                            // restoring
        ArmorClass{armor_value, armor_location, protecting_effect_initializer},  // protecting
        Damage{damage_value, damage_effect}};                                    // damaging

    // constructor: properties set from references
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore,     // restoring
        protection,  // protecting
        damage};     // damaging

    // constructor: properties set from const references
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        const_restore,     // restoring
        const_protection,  // protecting
        const_damage};     // damaging

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
