#pragma once
#include "DefaultWeapon.hpp"
#include "Object/DefaultStrategies.hpp"

struct CustomWeapon {  // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
    Name name;
    std::vector<DefaultWeapon> others{// will be used in AttackStrategy_<CustomWeapon>
                                      DefaultWeapon{Name{"Light weapon"}, Damage{10}},
                                      DefaultWeapon{Name{"Medium weapon"}, Damage{20, DamageType::Magical, Effect{EffectType::Burn}}}};
};

static_assert(Damagingable<DefaultWeapon>);
static_assert(not Damagingable<CustomWeapon>);

template <std::convertible_to<CustomWeapon> T>
struct AttackStrategy_<T> {
    // ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const {  // when get Damagingable property
    //     auto* suspect = Whom(owner, target);
    //     ActionStatus base_status = default_attack_behavior(obj, suspect);

    //     for (Damagingable auto& other : obj.others) {
    //         default_attack_behavior(other, suspect);
    //         std::cout << "\t\t " << other << "\n";
    //     }
    //     return base_status;
    // }

    ActionStatus operator()(auto& obj, Object* owner, Object* target) const {  // CustomWeapon is not Damagingable by default
        auto* suspect = Whom(owner, target);
        ActionStatus status{ActionStatus::None};

        if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) {  // when got Damagingable property
            status = default_attack_behavior(obj, suspect);
        } else {
            std::cout << '\n';
        }

        for (Damagingable auto& other : obj.others) {
            status = default_attack_behavior(other, suspect);
            std::cout << "\t\t " << other << '\n';
        }
        return status;
    }
};
