#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/EffectTypeContainer/EffectTypeContainer.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {

// MARK: RestoringSimple_

template <typename T>
class RestoringSimple_ : public T {
public:
    using property_data = PropertyData<RestoringSimple_, T>;
    using hold_type = EffectTypeContainer;

    RestoringSimple_() = default;

    template <typename... INFO, typename... Args>
    RestoringSimple_(const Name& name, std::tuple<INFO...>&& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::make_from_tuple<hold_type>(std::move(restoreEffects))} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create EffectTypeContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
    RestoringSimple_(const Name& name, const std::tuple<INFO...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::make_from_tuple<hold_type>(restoreEffects)} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create EffectTypeContainer from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    RestoringSimple_(const Token&, Args&&... args)
        : T{} {
        auto fn = []<typename A>(auto* th, [[maybe_unused]] A& arg) {
            if constexpr (std::same_as<std::remove_cvref_t<A>, hold_type>) {
                th->getType() = std::forward<A>(arg);
            } else {
                trait<std::remove_cvref_t<A>>::get(static_cast<T&>(*th)) = std::forward<A>(arg);
            }
        };

        ((fn(this, args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit RestoringSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    RestoringSimple_(const Name& name)
        : T{name} {}

    template <typename... Args>
    RestoringSimple_(const Name& name, [[maybe_unused]] decltype(std::ignore) restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    RestoringSimple_(const Name& name, hold_type&& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects_{std::move(restoreEffects)} {}

    template <typename... Args>
    RestoringSimple_(const Name& name, const hold_type& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects_{restoreEffects} {}

    template <typename... Args>
    RestoringSimple_(const Name& name, std::initializer_list<EffectType> restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...}, restoreEffects_{restoreEffects} {}

    template <typename... V, typename... Args>
        requires contains_type<hold_type, V...>
    RestoringSimple_(const Name& name, const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          restoreEffects_{std::get_if<hold_type>(&restoreEffects)
                              ? std::get<hold_type>(restoreEffects)
                              : hold_type{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<hold_type, V...>
    RestoringSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& restoreEffects, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    RestoringSimple_(hold_type&& restoreEffects, Args&&... args)
        : T{std::forward<Args>(args)...}, restoreEffects_{std::move(restoreEffects)} {}

    // MARK: getRestoreEffects

    constexpr auto& getRestoreEffects(this auto& self) {
        return self.restoreEffects_;
    }

    constexpr auto& getType(this auto& self) {  //? this fix accessibility
        return self.restoreEffects_;
    }

private:
    hold_type restoreEffects_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
