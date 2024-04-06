#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Concepts/Types/Name.hpp"
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Strategies/Premade/HealStrategy.hpp"

namespace impl {
constinit char healing_type_name[] = "Healing";

template <typename T>
struct Healing_ : T {
    using property_data = PropertyData<healing_type_name, Healing_, T>;

    Healing_() = default;

    template <typename... INFO, typename... Args>
    Healing_(const Name& name, std::tuple<INFO...>&& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth{std::make_from_tuple<CureHealth>(std::move(cureHealth))} {}

    template <typename... INFO, typename... Args>
    Healing_(const Name& name, const std::tuple<INFO...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth{std::make_from_tuple<CureHealth>(cureHealth)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<CureHealth, INFO...>)
    Healing_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create CureHealth from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<CureHealth, INFO...>)
    Healing_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create CureHealth from given tuple.");
    }

    Healing_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Healing_(const Name& name, [[maybe_unused]] decltype(std::ignore) cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Healing_(const Name& name, CureHealth&& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, cureHealth{std::move(cureHealth)} {}

    template <typename... Args>
    Healing_(const Name& name, const CureHealth& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, cureHealth{cureHealth} {}

    template <typename... V, typename... Args>
        requires type_is_possible<CureHealth, V...>
    Healing_(const Name& name, const std::variant<V...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth{std::get_if<CureHealth>(&cureHealth)
                         ? std::get<CureHealth>(cureHealth)
                         : CureHealth{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<CureHealth, V...>
    Healing_(const Name& name, [[maybe_unused]] const std::variant<V...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

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