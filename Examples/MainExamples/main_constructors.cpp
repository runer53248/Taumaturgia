#include <iostream>
#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Usage/Properties.hpp"
#include "Usage/DefaultStrategies.hpp"

struct Potion {
    Name name;
};

constinit const Effect damage_effect{EffectType::Bleed};
constinit const auto armor_value{4};
constinit const auto armor_location{BodyLocation::Internal};
constinit const auto damage_value{10};

int main() {
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

    // MARK: set all from lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore,     // restoring
        protection,  // protecting
        damage};     // damaging

    // MARK: set all from const lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        const_restore,     // restoring
        const_protection,  // protecting
        const_damage};     // damaging

    // MARK: set all from move types or initializer_list
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore_effect_initializer,                                              // restoring
        ArmorClass{armor_value, armor_location, protecting_effect_initializer},  // protecting
        Damage{damage_value, damage_effect}};                                    // damaging

    // MARK: set all from tuples by rvalues
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::tuple(restore_effect_initializer),                                  // restoring
        std::tuple(armor_value, armor_location, protecting_effect_initializer),  // protecting
        std::tuple(damage_value, damage_effect)};                                // damaging

    std::tuple restoring_tuple(restore_effect_initializer);
    std::tuple protecting_tuple(armor_value, armor_location, protecting_effect_initializer);
    std::tuple damaging_tuple(damage_value, damage_effect);

    // MARK: set all from tuples by lvalues
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restoring_tuple,   // restoring
        protecting_tuple,  // protecting
        damaging_tuple};   // damaging

    // MARK: set last from lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,  // restoring
        std::ignore,  // protecting
        damage};      // damaging

    // MARK: set last from rvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                           // restoring
        std::ignore,                           // protecting
        Damage{damage_value, damage_effect}};  // damaging

    // MARK: set last from tuple by lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,      // restoring
        std::ignore,      // protecting
        damaging_tuple};  // damaging

    // MARK: set last from tuple by rvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                               // restoring
        std::ignore,                               // protecting
        std::tuple{damage_value, damage_effect}};  // damaging

    // MARK: set first
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore_effect_initializer};  // restoring

    // MARK: all properties default
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name};

// TODO: fix ambigious calls
#ifndef NO_PREMADE_PROPERTIES
    // MARK: incorrect tuple
    try {
        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            std::tuple{"test"},
            std::ignore,
            std::tuple{"test"}};  // damaging
    } catch (const std::logic_error& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    // MARK: incorrect tuple
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

    // MARK: incorrect tuple
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
#endif

    using container = std::variant<std::monostate, Damage, Protection, EffectTypeContainer>;

    // MARK: set from moved types or initializer_list
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        {restore_effect_initializer},                                            // restoring
        ArmorClass{armor_value, armor_location, protecting_effect_initializer},  // protecting
        Damage{damage_value, damage_effect}};                                    // damaging

    // MARK: set from lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        restore,     // restoring
        protection,  // protecting
        damage};     // damaging

    // MARK: set from const lvalue
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        const_restore,     // restoring
        const_protection,  // protecting
        const_damage};     // damaging

    // MARK: set from variants
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        container{restore},     // restoring
        container{protection},  // protecting
        container{damage}};     // damaging

    // MARK: set from variants (conditional check)
    try {
        restoring_protecting_damaging_potion{
            spiked_shield_potion_name,
            container{damage},   // restoring
            container{damage},   // protecting
            container{damage}};  // damaging
    } catch (const std::bad_variant_access& err) {
        std::cout << "exception: " << err.what() << '\n';
    }

    std::variant<std::monostate, Damage> damage_variant{damage};

    // MARK: set if correct variant given
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        damage_variant,   // restoring
        damage_variant,   // protecting
        damage_variant};  // damaging
}
