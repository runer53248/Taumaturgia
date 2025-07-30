#pragma once
#include "DefaultWeapon.hpp"
#include "Usage/DefaultStrategies.hpp"

struct WithDefaultWeaponVector {
    std::vector<DefaultWeapon> others{
        // will be used in AttackStrategy_<CustomWeaponBuild> / UserStrategy_<Damage, CustomWeaponBuild>
        DefaultWeapon{Name{"Light weapon"}, Damage{10}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{20, DamageType::Magical}},
        DefaultWeapon{Name{"Flames"}, Damage{0, Effect{EffectType::Burn}}}
    };
};
using CustomWeaponBuild = add_properties_ordered<
    WithDefaultWeaponVector,
    Naming>;

struct CustomWeaponClass {  // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
    Name name;
    std::vector<DefaultWeapon> others{
        // will be used in AttackStrategy_<CustomWeaponClass> / UserStrategy_<Damage, CustomWeaponClass>
        DefaultWeapon{Name{"Light weapon"}, Damage{10}},
        DefaultWeapon{Name{"Medium weapon"}, Damage{20, DamageType::Magical}},
        DefaultWeapon{Name{"Flames"}, Damage{0, Effect{EffectType::Burn}}}
    };
};

#ifdef WITH_ADD_PROPERTIES
using CustomWeapon = CustomWeaponBuild;
#else
using CustomWeapon = CustomWeaponClass;
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
                // std::random_shuffle(obj.others.begin(), obj.others.end());
                for (auto& other : obj.others) {
                    status = default_attack_behavior(other, suspect);
                    std::cout << "\t\t " << other << '\n';
                }
            }
        }
        return status;
    }
};
