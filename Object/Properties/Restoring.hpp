#pragma once
#include <boost/mp11.hpp>
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/RestoreStrategy.hpp"
#include "Helpers/PropertyData.hpp"

namespace impl {
constexpr char restoring_type_name[] = "Restoring";

template <typename T>
struct Restoring_ : T {
    using property_data = PropertyData<restoring_type_name, Restoring_, T>;

    Restoring_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<EffectTypeContainer, INFO...> and sizeof...(INFO) > 0)
    Restoring_(const Name& name, std::tuple<INFO...>&& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{std::move(std::make_from_tuple<EffectTypeContainer>(std::forward<decltype(restoreEffects)>(restoreEffects)))} {}

    Restoring_(const Name& name)
        : T{name} {}

    Restoring_(const Name& name, [[maybe_unused]] decltype(std::ignore) restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Restoring_(const Name& name, EffectTypeContainer&& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{std::move(restoreEffects)} {}

    Restoring_(const Name& name, const EffectTypeContainer& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{restoreEffects} {}

    Restoring_(const Name& name, std::initializer_list<EffectType> restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{restoreEffects} {}

    template <typename... V>
        requires(boost::mp11::mp_contains<std::variant<V...>, EffectTypeContainer>::value and (sizeof...(V) > 0))
    Restoring_(const Name& name, const std::variant<V...>& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{std::get<EffectTypeContainer>(restoreEffects)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, EffectTypeContainer>::value and (sizeof...(V) > 0))
    Restoring_(const Name& name, [[maybe_unused]] const std::variant<V...>& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

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

template <typename T>
struct RestoreStrategy_<impl::Restoring_<T>> : RestoreStrategy_<T> {};  // forward eventualy implemented strategy
