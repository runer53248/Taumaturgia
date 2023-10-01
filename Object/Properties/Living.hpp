#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/AliveStrategy.hpp"
#include "PropertyData.hpp"

constexpr char living_type_name[] = "Living";

template <typename T>
struct Living_ : T {
    using property_data = PropertyData<Living_, T, living_type_name>;

    Living_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Health, INFO...> and sizeof...(INFO) > 0)
    Living_(const Name& name, std::tuple<INFO...>&& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::move(std::make_from_tuple<Health>(std::forward<decltype(hp)>(hp)))} {}

    Living_(const Name& name)
        : T{name} {}
    
    Living_(const Name& name, decltype(std::ignore), auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Living_(const Name& name, Health&& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::move(hp)} {}

    Living_(const Name& name, const Health& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{hp} {}

    auto& getHp() {
        return hp;
    }

    const auto& getHp() const {
        return hp;
    }

private:
    Health hp{};
};

namespace Test {
struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);
}  // namespace Test

template <typename T>
using Living = std::conditional_t<Livingable<T>, T, Living_<T>>;
