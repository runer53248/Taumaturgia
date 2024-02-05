#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/HealStrategy.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char healing_type_name[] = "Healing";

template <typename T>
struct Healing_ : T {
    using property_data = PropertyData<healing_type_name, Healing_, T>;

    Healing_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Health, INFO...> and sizeof...(INFO) > 0)
    Healing_(const Name& name, std::tuple<INFO...>&& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...},
          cureHealth{std::move(std::make_from_tuple<CureHealth>(std::forward<decltype(cureHealth)>(cureHealth)))} {}

    Healing_(const Name& name)
        : T{name} {}

    Healing_(const Name& name, [[maybe_unused]] decltype(std::ignore) cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Healing_(const Name& name, CureHealth&& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{std::move(cureHealth)} {}

    Healing_(const Name& name, const CureHealth& cureHealth, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, cureHealth{cureHealth} {}

    auto& getCureHealth() & {
        return cureHealth;
    }

    const auto& getCureHealth() const& {
        return cureHealth;
    }

private:
    CureHealth cureHealth{};
};

namespace Test {
struct Healing_Test {};
static_assert(Healingable<Healing_<Healing_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Healing = std::conditional_t<Healingable<T>, T, impl::Healing_<T>>;

template <typename T>
struct HealStrategy_<impl::Healing_<T>> : HealStrategy_<T> {};  // forward eventualy implemented strategy
