#pragma once
#include "DefaultWeapon.hpp"
#include "Usage/DefaultStrategies.hpp"

#ifdef WITH_ADD_PROPERTIES
struct WithDefaultWeaponVector {
    std::vector<DefaultWeapon> others{
        // will be used in AttackStrategy_<CustomWeapon> / UserStrategy_<Damage, CustomWeapon>
        DefaultWeapon{Name{"Light weapon"}, Damage{10}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{20, DamageType::Magical, Effect{EffectType::Burn}}}};
};
using CustomWeapon = add_properties_ordered<
    WithDefaultWeaponVector,
    Naming>;
#else

struct CustomWeapon {  // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
    Name name;
    std::vector<DefaultWeapon> others{
        // will be used in AttackStrategy_<CustomWeapon> / UserStrategy_<Damage, CustomWeapon>
        DefaultWeapon{Name{"Light weapon"}, Damage{10}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{20, DamageType::Magical, Effect{EffectType::Burn}}}};
};

#endif

static_assert(Damagingable<DefaultWeapon>);
static_assert(not Damagingable<CustomWeapon>);

template <std::convertible_to<CustomWeapon> T>
#ifdef NO_PREMADE_STRATEGIES
struct UserStrategy_<Damage, T> {
#else
struct AttackStrategy_<T> {
#endif

    // other way: when get Damagingable property
    // constexpr ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const {
    // ...
    // }

    static constexpr ActionStatus operator()(auto& obj, Object* owner, Object* target) {  // CustomWeapon is not Damagingable by default
        auto* suspect = Whom(owner, target);
        ActionStatus status{ActionStatus::None};

        if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) {  // when got Damagingable property
            status = default_attack_behavior(obj, suspect);
        } else {
            std::cout << '\n';
        }

        if constexpr (requires { obj.others; }) {
            if constexpr (Damagingable<typename decltype(obj.others)::value_type>) {
                for (auto& other : obj.others) {
                    status = default_attack_behavior(other, suspect);
                    std::cout << "\t\t " << other << '\n';
                }
            }
        }
        return status;
    }
};
