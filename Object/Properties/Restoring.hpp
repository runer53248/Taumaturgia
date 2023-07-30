#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/RestoreStrategy.hpp"

template <typename T>
struct Restoring_ : T {
    template <typename... INFO>
        requires(std::is_constructible_v<EffectTypeContainer, INFO...> and sizeof...(INFO) > 0)
    Restoring_(const Name& name, std::tuple<INFO...>&& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{std::move(std::make_from_tuple<EffectTypeContainer>(std::forward<decltype(restoreEffects)>(restoreEffects)))} {}

    Restoring_(const Name& name, decltype(std::ignore), auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Restoring_(const Name& name, EffectTypeContainer&& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{std::move(restoreEffects)} {}

    Restoring_(const Name& name, const EffectTypeContainer& restoreEffects, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, restoreEffects{restoreEffects} {}

    auto& getRestoreEffects() {
        return restoreEffects;
    }

    const auto& getRestoreEffects() const {
        return restoreEffects;
    }

private:
    EffectTypeContainer restoreEffects{};
};

namespace Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace Test

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, Restoring_<T>>;

template <typename T>
struct RestoreStrategy_<Restoring_<T>> : RestoreStrategy_<T> {};  // forward eventualy implemented strategy
