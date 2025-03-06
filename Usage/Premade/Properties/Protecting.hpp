#pragma once
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/Protection/Protection.hpp"
#include "buildin_defaults.hpp"

namespace impl {
inline constinit const char protecting_type_name[] = "Protecting";

template <typename T>
class Protecting_ : public T {
public:
    using property_data = PropertyData<protecting_type_name, Protecting_, T>;
    using hold_type = Protection;

    template <typename TARGET>
    using apply = std::conditional_t<Protectingable<TARGET>, TARGET, impl::Protecting_<TARGET>>;

    Protecting_() = default;

    template <typename... INFO, typename... Args>
    constexpr Protecting_(const Name& name, std::tuple<INFO...>&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(std::move(protection))} {
        static_assert(constructible_from_args<Protection, INFO...>, "Can't create Protection from given tuple.");
    }

    template <typename... INFO, typename... Args>
    constexpr Protecting_(const Name& name, const std::tuple<INFO...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(protection)} {
        static_assert(constructible_from_args<Protection, INFO...>, "Can't create Protection from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Protecting_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit Protecting_(TT&& t)  // explicit is important
        : T{std::forward<TT>(t)} {}

    Protecting_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Protecting_(const Name& name, [[maybe_unused]] decltype(std::ignore) protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Protecting_(const Name& name, Protection&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    template <typename... Args>
    Protecting_(const Name& name, const Protection& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection_{protection} {}

    template <typename... V, typename... Args>
        requires contains_type<Protection, V...>
    Protecting_(const Name& name, const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::get_if<Protection>(&protection)
                          ? std::get<Protection>(protection)
                          : Protection{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<Protection, V...>
    Protecting_(const Name& name, [[maybe_unused]] const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    Protecting_(Protection&& protection, Args&&... args)
        : T{std::forward<Args>(args)...}, protection_{std::move(protection)} {}

    // MARK: getProtection

    constexpr auto& getProtection(this auto& self) {
        return self.protection_;
    }

private:
    Protection protection_ = buildin_defaults<Protection>::get();
};

}  // namespace impl

namespace impl::Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace impl::Test

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, impl::Protecting_<T>>;
