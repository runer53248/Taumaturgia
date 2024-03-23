#include <iostream>
#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Object/DefaultStrategies.hpp"
#include "Object/Properties/Properties.hpp"

struct Potion {
    Name name;
};

int main() {
    Name spiked_shield_potion_name{"Spiked Shield Potion"};

    Protecting<Damaging<Potion>>{
        spiked_shield_potion_name,
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},
        Damage{10, Effect{EffectType::Bleed}}};

    Damaging<Protecting<Potion>>{
        spiked_shield_potion_name,
        Damage{10, Effect{EffectType::Bleed}},
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}}};

    using restoring_protecting_damaging_potion = Restoring<Protecting<Damaging<Potion>>>;

    // constructor: all properties set
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        {EffectType::Sleep, EffectType::Sleep},                      // restoring
        ArmorClass{4, BodyLocation::Internal, {EffectType::Sleep}},  // protecting
        Damage{10, Effect{EffectType::Bleed}}};                      // damaging

    // constructor: ignoring first 2 properties
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::ignore,                             // restoring
        std::ignore,                             // protecting
        Damage{10, Effect{EffectType::Bleed}}};  // damaging

    // constructor: first property only
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        {EffectType::Sleep, EffectType::Sleep}};  // restoring

    // constructor: all properties default
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name};

    // constructor: properties set from tuples
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::make_tuple(std::initializer_list{EffectType::Sleep, EffectType::Sleep}),          // restoring
        std::make_tuple(4, BodyLocation::Internal, std::initializer_list{EffectType::Sleep}),  // protecting
        std::make_tuple(10, Effect{EffectType::Bleed})};                                       // damaging

    // constructor: first property set from tuple
    restoring_protecting_damaging_potion{
        spiked_shield_potion_name,
        std::make_tuple(EffectType::Sleep)};  // restoring

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

    EffectTypeContainer restore{{EffectType::Sleep, EffectType::Sleep}};
    Protection protection{ArmorClass{4, BodyLocation::Internal, std::initializer_list{EffectType::Sleep}}};
    Damage damage{10, Effect{EffectType::Bleed}};

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
