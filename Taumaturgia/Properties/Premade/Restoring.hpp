#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Concepts/Restoringable.hpp"
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Types/Name.hpp"

namespace impl {
inline constinit char restoring_type_name[] = "Restoring";

template <typename T>
struct Restoring_ : T {
    using property_data = PropertyData<restoring_type_name, Restoring_, T>;

    Restoring_() = default;

    template <typename... INFO, typename... Args>
    Restoring_(const Name& name, std::tuple<INFO...>&& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects{std::make_from_tuple<EffectTypeContainer>(std::move(restoreEffects))} {}

    template <typename... INFO, typename... Args>
    Restoring_(const Name& name, const std::tuple<INFO...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects{std::make_from_tuple<EffectTypeContainer>(restoreEffects)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<EffectTypeContainer, INFO...>)
    Restoring_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create EffectTypeContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<EffectTypeContainer, INFO...>)
    Restoring_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create EffectTypeContainer from given tuple.");
    }

    Restoring_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Restoring_(const Name& name, [[maybe_unused]] decltype(std::ignore) restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Restoring_(const Name& name, EffectTypeContainer&& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects{std::move(restoreEffects)} {}

    template <typename... Args>
    Restoring_(const Name& name, const EffectTypeContainer& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects{restoreEffects} {}

    template <typename... Args>
    Restoring_(const Name& name, std::initializer_list<EffectType> restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects{restoreEffects} {}

    template <typename... V, typename... Args>
        requires type_is_possible<EffectTypeContainer, V...>
    Restoring_(const Name& name, const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects{std::get_if<EffectTypeContainer>(&restoreEffects)
                             ? std::get<EffectTypeContainer>(restoreEffects)
                             : EffectTypeContainer{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<EffectTypeContainer, V...>
    Restoring_(const Name& name, [[maybe_unused]] const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    auto& getRestoreEffects() & {
        return restoreEffects;
    }

    const auto& getRestoreEffects() const& {
        return restoreEffects;
    }

private:
    EffectTypeContainer restoreEffects{};
};

namespace Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, impl::Restoring_<T>>;
