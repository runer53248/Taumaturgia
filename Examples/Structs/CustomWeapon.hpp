#pragma once
#include "DefaultWeapon.hpp"
#include "Object/DefaultStrategies.hpp"

struct CustomWeapon {  // is not Damagingable but still counts as AttackStrategable because have custom AttackStrategy_
    Name name;
    std::vector<DefaultWeapon> others{// will be used in AttackStrategy_<CustomWeapon>
                                      DefaultWeapon{Name{"Light weapon"}, Damage{10}},
                                      DefaultWeapon{Name{"Medium weapon"}, Damage{20}}};
};

static_assert(Damagingable<DefaultWeapon>);
static_assert(not Damagingable<CustomWeapon>);

template <>
struct AttackStrategy_<CustomWeapon> {
    // ActionStatus operator()(Damagingable auto& obj, Object* owner, Object* target) const {  // when get Damagingable property
    //     auto* suspect = Whom(owner, target);
    //     ActionStatus base_status = default_attack_behavior(obj, suspect);

    //     for (auto& other : obj.others) {
    //         default_attack_behavior(other, suspect);
    //         print_subAttacks(other);
    //     }
    //     return base_status;
    // }

    ActionStatus operator()(auto& obj, Object* owner, Object* target) const {  // CustomWeapon is not Damagingable by default
        auto* suspect = Whom(owner, target);
        ActionStatus status{ActionStatus::None};

        if constexpr (Damagingable<std::remove_reference_t<decltype(obj)>>) {  // when got Damagingable property
            status = default_attack_behavior(obj, suspect);
        }

        for (auto& other : obj.others) {
            status = default_attack_behavior(other, suspect);
            print_subAttacks(other);
        }
        return status;
    }

    bool print_subAttacks(Damagingable auto& obj) const {
        std::cout << "\t\t " << obj << "\n";
        return true;
    }
};
