#pragma once
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"

namespace impl {

// MARK: ProtectingSimple_

template <typename T>
class ProtectingSimple_ : public T {
public:
    using property_data = PropertyData<ProtectingSimple_, T>;
    using hold_type = Protection;

    ProtectingSimple_() = default;

    template <typename... INFO, typename... Args>
    constexpr ProtectingSimple_(const Name& name, std::tuple<INFO...>&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(std::move(protection))} {
        static_assert(constructible_from_args<Protection, INFO...>, "Can't create Protection from given tuple.");
    }

    template <typename... INFO, typename... Args>
    constexpr ProtectingSimple_(const Name& name, const std::tuple<INFO...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(protection)} {
        static_assert(constructible_from_args<Protection, INFO...>, "Can't create Protection from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    ProtectingSimple_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
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
    ProtectingSimple_(const Name& name, Protection&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    template <typename... Args>
    ProtectingSimple_(const Name& name, const Protection& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{protection} {}

    template <typename... V, typename... Args>
        requires contains_type<Protection, V...>
    ProtectingSimple_(const Name& name, const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::get_if<Protection>(&protection)
                          ? std::get<Protection>(protection)
                          : Protection{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<Protection, V...>
    ProtectingSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    ProtectingSimple_(Protection&& protection, Args&&... args)
        : T{std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    // MARK: getProtection

    constexpr auto& getProtection(this auto& self) {
        return self.protection_;
    }

private:
    Protection protection_ = buildin_defaults<Protection>::get();
};

}  // namespace impl
