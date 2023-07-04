#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/RestoreStrategy.hpp"

template <typename T>
struct Restoring_ : T {
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

struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, Restoring_<T>>;

template <typename T>
struct RestoreStrategy_<Restoring_<T>> : RestoreStrategy_<T> {};  // forward eventualy implemented strategy
