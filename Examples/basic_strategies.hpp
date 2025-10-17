#include "Taumaturgia/Object/Object.hpp"
#include "Taumaturgia/Strategies/Defaults/DefaultGetterStrategy.hpp"
#include "Usage/Enums/AliveStatus.hpp"

template <typename TYPE>
struct UserStrategy_<TYPE, Default> {
    static constexpr std::optional<AliveStatus> operator()(Livingable auto&) {
        return AliveStatus::Living;
    }

    static constexpr ActionStatus operator()(auto&, Object*, Object*) {
        return ActionStatus::Success;
    }
};
