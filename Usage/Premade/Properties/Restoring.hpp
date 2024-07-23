#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Usage/Types/EffectTypeContainer/EffectTypeContainer.hpp"
#include "Usage/Types/Name/Name.hpp"

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
          restoreEffects_{std::make_from_tuple<EffectTypeContainer>(std::move(restoreEffects))} {
        static_assert(constructible_from_args<EffectTypeContainer, INFO...>, "Can't create EffectTypeContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
    Restoring_(const Name& name, const std::tuple<INFO...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::make_from_tuple<EffectTypeContainer>(restoreEffects)} {
        static_assert(constructible_from_args<EffectTypeContainer, INFO...>, "Can't create EffectTypeContainer from given tuple.");
    }

    // !

    template <typename... Args>
    Restoring_(const Token&, Args&&... args)
        : T{} {
        ((trait<Args>::get(*this) = std::forward<Args>(args)),...);
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

    // MARK: nameless C-tor

    template <typename... Args>
    Restoring_(EffectTypeContainer&& restoreEffects, Args&&... args)
        : T{std::forward<Args>(args)...}, restoreEffects_{std::move(restoreEffects)} {}

    // MARK: getRestoreEffects

    constexpr auto& getRestoreEffects(this auto& self) {
        return self.restoreEffects_;
    }

private:
    EffectTypeContainer restoreEffects_{};
};

}  // namespace impl

namespace impl::Test {
struct Restoring_Test {};
static_assert(Restoringable<Restoring_<Restoring_Test>>);
}  // namespace impl::Test

template <typename T>
using Restoring = std::conditional_t<Restoringable<T>, T, impl::Restoring_<T>>;
