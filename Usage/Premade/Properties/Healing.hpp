#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Features.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/CureHealth/CureHealth.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "buildin_defaults.hpp"

namespace impl {

template <typename T>
class HealingSimple_ : public T {
public:
    using property_data = PropertyData<HealingSimple_, T>;
    using hold_type = CureHealth;

    HealingSimple_() = default;

    template <typename... INFO, typename... Args>
    HealingSimple_(const Name& name, std::tuple<INFO...>&& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth_{std::make_from_tuple<CureHealth>(std::move(cureHealth))} {
        static_assert(constructible_from_args<CureHealth, INFO...>, "Can't create CureHealth from given tuple.");
    }

    template <typename... INFO, typename... Args>
    HealingSimple_(const Name& name, const std::tuple<INFO...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth_{std::make_from_tuple<CureHealth>(cureHealth)} {
        static_assert(constructible_from_args<CureHealth, INFO...>, "Can't create CureHealth from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    HealingSimple_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit HealingSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    HealingSimple_(const Name& name)
        : T{name} {}

    template <typename... Args>
    HealingSimple_(const Name& name, [[maybe_unused]] decltype(std::ignore) cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    HealingSimple_(const Name& name, CureHealth&& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, cureHealth_{std::move(cureHealth)} {}

    template <typename... Args>
    HealingSimple_(const Name& name, const CureHealth& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...}, cureHealth_{cureHealth} {}

    template <typename... V, typename... Args>
        requires contains_type<CureHealth, V...>
    HealingSimple_(const Name& name, const std::variant<V...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          cureHealth_{std::get_if<CureHealth>(&cureHealth)
                          ? std::get<CureHealth>(cureHealth)
                          : CureHealth{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<CureHealth, V...>
    HealingSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& cureHealth, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    HealingSimple_(CureHealth&& cureHealth, Args&&... args)
        : T{std::forward<Args>(args)...}, cureHealth_{std::move(cureHealth)} {}

    // MARK: getCureHealth

    constexpr auto& getCureHealth(this auto& self) {
        return self.cureHealth_;
    }

private:
    CureHealth cureHealth_ = buildin_defaults<CureHealth>::get();
};

template <typename T>
class Healing_ : public Features_<HealingSimple_<T>> {
public:
    using property_data = PropertyData<Healing_, T>;
    using child = Features_<HealingSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Healing_Test {};
static_assert(Healingable<Healing_<Healing_Test>>);
}  // namespace impl::Test

template <typename T>
using Healing = std::conditional_t<Healingable<T>, T, impl::Healing_<T>>;
