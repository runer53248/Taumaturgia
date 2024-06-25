#pragma once
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Types/Name.hpp"
#include "Taumaturgia/Types/Protection.hpp"

namespace impl {
inline constinit const char protecting_type_name[] = "Protecting";

template <typename T>
class Protecting_ : public T {
public:
    using property_data = PropertyData<protecting_type_name, Protecting_, T>;

    Protecting_() = default;

    template <typename... INFO, typename... Args>
    Protecting_(const Name& name, std::tuple<INFO...>&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(std::move(protection))} {}

    template <typename... INFO, typename... Args>
    Protecting_(const Name& name, const std::tuple<INFO...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection_{std::make_from_tuple<Protection>(protection)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Protection, INFO...>)
    Protecting_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create Protection from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Protection, INFO...>)
    Protecting_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create Protection from given tuple.");
    }

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

    constexpr auto& getProtection(this auto& self) {
        return self.protection_;
    }

private:
    Protection protection_{};
};

}  // namespace impl

#ifdef WITH_ADD_PROPERTIES
#include "Taumaturgia/Traits/UserTypeTraits.hpp"
template <typename T>
struct traits::CustomAccessType<Protection, T> {
    static constexpr decltype(auto) get(GetProtectionAccessable auto& el) {
        return el.getProtection();
    }
};
#endif

namespace impl::Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace impl::Test

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, impl::Protecting_<T>>;
