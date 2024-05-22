#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Traits/RestoreEffectsTraits.hpp"
#include "Taumaturgia/Types/EffectTypeContainer.hpp"
#include "Taumaturgia/Types/Name.hpp"

namespace impl {
inline constinit const char restoring_type_name[] = "Restoring";

template <typename T>
class Restoring_ : public T {
public:
    using property_data = PropertyData<restoring_type_name, Restoring_, T>;

    Restoring_() = default;

    template <typename... INFO, typename... Args>
    Restoring_(const Name& name, std::tuple<INFO...>&& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::make_from_tuple<EffectTypeContainer>(std::move(restoreEffects))} {}

    template <typename... INFO, typename... Args>
    Restoring_(const Name& name, const std::tuple<INFO...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::make_from_tuple<EffectTypeContainer>(restoreEffects)} {}

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
        : T{name, std::forward<Args>(args)...}, restoreEffects_{std::move(restoreEffects)} {}

    template <typename... Args>
    Restoring_(const Name& name, const EffectTypeContainer& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects_{restoreEffects} {}

    template <typename... Args>
    Restoring_(const Name& name, std::initializer_list<EffectType> restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects_{restoreEffects} {}

    template <typename... V, typename... Args>
        requires contains_type<EffectTypeContainer, V...>
    Restoring_(const Name& name, const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::get_if<EffectTypeContainer>(&restoreEffects)
                              ? std::get<EffectTypeContainer>(restoreEffects)
                              : EffectTypeContainer{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<EffectTypeContainer, V...>
    Restoring_(const Name& name, [[maybe_unused]] const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    constexpr auto& getRestoreEffects(this auto& self) {
        return self.restoreEffects_;
    }

private:
    EffectTypeContainer restoreEffects_{};
};

}  // namespace impl

#ifdef WITH_ADD_PROPERTIES
#include "Taumaturgia/Traits/UserTypeTraits.hpp"
template <typename T>
struct traits::CustomAccessType<EffectTypeContainer, T> {
    static constexpr decltype(auto) get(GetRestoreEffectsAccessable auto& el) {
        return el.getRestoreEffects();
    }
};
#endif

namespace impl::Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace impl::Test

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, impl::Restoring_<T>>;
