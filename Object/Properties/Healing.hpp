#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/HealStrategy.hpp"
#include "PropertyData.hpp"

constexpr char healing_type_name[] = "Healing";

template <typename T>
struct Healing_ : T {
    using property_data = PropertyData<Healing_, T, healing_type_name>;

    Healing_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Health, INFO...> and sizeof...(INFO) > 0)
    Healing_(const Name& name, std::tuple<INFO...>&& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...},
          cureHealth{std::move(std::make_from_tuple<Health>(std::forward<decltype(cureHealth)>(cureHealth)))} {}

    Healing_(const Name& name)
        : T{name} {}

    Healing_(const Name& name, [[maybe_unused]] decltype(std::ignore) cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Healing_(const Name& name, Health&& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{std::move(cureHealth)} {}

    Healing_(const Name& name, const Health& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{cureHealth} {}

    auto& getCureHealth() & {
        return cureHealth;
    }

    const auto& getCureHealth() const& {
        return cureHealth;
    }

private:
    Health cureHealth{};
};

namespace Test {
struct Healing_Test {};
static_assert(Healingable<Healing_<Healing_Test>>);
}  // namespace Test

template <typename T>
using Healing = std::conditional_t<Healingable<T>, T, Healing_<T>>;

template <typename T>
struct HealStrategy_<Healing_<T>> : HealStrategy_<T> {};  // forward eventualy implemented strategy
