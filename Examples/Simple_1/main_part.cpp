#include <print>
#include <vector>
#include "Examples/PreetyPrint/preety_print.hpp"
#include "Taumaturgia/Properties/UserProperty.hpp"

struct base {};

template <typename T>
using int_property = UserPropertyAdapter<int>::once<T>;

template <typename T>
using CureValueType_property = UserPropertyAdapter<CureValueType>::once<T>;

template <typename T>
using EffectContainer_property = UserPropertyAdapter<EffectContainer>::once<T>;

using CureHealthType = add_properties_ordered<
    base,
    int_property,
    CureValueType_property,
    EffectContainer_property>;

template <typename T>
struct std::formatter<std::pair<T, EffectState>> : std::formatter<std::string> {
    auto format(const std::pair<T, EffectState>& t, [[maybe_unused]] std::format_context& ctx) const {
        std::ostringstream o;
        o << t;
        return formatter<string>::format(std::move(o).str(), ctx);
    }
};

int main() {
    std::println();
    std::print("{}\n", std::pair{"Inactive", EffectState::Inactive});
    std::print("{}\n", std::pair{"Active", EffectState::Active});
    std::print("{}\n", std::pair{"Removed", EffectState::Removed});
    std::print("{}\n", std::pair{"Finished", EffectState::Finished});
    std::println();

    CureHealthType cureHealthType{
        5,
        CureValueType::CURRENT_PERCENT,
        EffectContainer{
            Effect{EffectType::Burn},
            Effect{EffectType::Devour, EffectState::Active},
            Effect{EffectType::Shock, Duration{3, DurationType::Minute}, EffectState::Finished},
            Effect{EffectType::Freeze, Duration{0, DurationType::Instant}, EffectState::Removed}}};

    std::print("int = {}\n", trait<int>::get(cureHealthType));
    std::print("CureValueType = {}\n", toString(trait<CureValueType>::get(cureHealthType)));
    std::print("EffectContainer = {}\n", trait<EffectContainer>::get(cureHealthType));
}
