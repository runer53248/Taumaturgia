#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"

namespace impl {

template <typename T>
class ProtectingSimple_ : public T {
public:
    using property_data = PropertyData<ProtectingSimple_, T>;
    using hold_type = Protection;

    ProtectingSimple_() = default;

    template <typename... INFO, typename... Args>
    constexpr ProtectingSimple_(const Name& name, std::tuple<INFO...>&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<hold_type>(std::move(protection))} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create Protection from given tuple.");
    }

    template <typename... INFO, typename... Args>
    constexpr ProtectingSimple_(const Name& name, const std::tuple<INFO...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<hold_type>(protection)} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create Protection from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    ProtectingSimple_(const Token&, Args&&... args)
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
    explicit ProtectingSimple_(TT&& t)  // explicit is important
        : T{std::forward<TT>(t)} {}

    ProtectingSimple_(const Name& name)
        : T{name} {}

    template <typename... Args>
    ProtectingSimple_(const Name& name, [[maybe_unused]] decltype(std::ignore) protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    ProtectingSimple_(const Name& name, hold_type&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    template <typename... Args>
    ProtectingSimple_(const Name& name, const hold_type& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{protection} {}

    template <typename... V, typename... Args>
        requires contains_type<hold_type, V...>
    ProtectingSimple_(const Name& name, const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::get_if<hold_type>(&protection)
                          ? std::get<hold_type>(protection)
                          : hold_type{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<hold_type, V...>
    ProtectingSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    ProtectingSimple_(hold_type&& protection, Args&&... args)
        : T{std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    // MARK: getProtection

    constexpr auto& getProtection(this auto& self) {
        return self.protection_;
    }

    constexpr decltype(auto) getType(this auto& self) {  //? this fix accessibility
        return (self.protection_);
    }

private:
    hold_type protection_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
