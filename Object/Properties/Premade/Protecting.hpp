#pragma once
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Properties/Helpers/PropertyData.hpp"
#include "Object/Properties/Helpers/constructible_from_args.hpp"
#include "Object/Strategies/Premade/DefendStrategy.hpp"

namespace impl {
constinit char protecting_type_name[] = "Protecting";

template <typename T>
struct Protecting_ : T {
    using property_data = PropertyData<protecting_type_name, Protecting_, T>;

    Protecting_() = default;

    template <typename... INFO, typename... Args>
    Protecting_(const Name& name, std::tuple<INFO...>&& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection{std::make_from_tuple<Protection>(std::move(protection))} {}

    template <typename... INFO, typename... Args>
    Protecting_(const Name& name, const std::tuple<INFO...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection{std::make_from_tuple<Protection>(protection)} {}

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
        : T{name, std::forward<Args>(args)...}, protection{std::move(protection)} {}

    template <typename... Args>
    Protecting_(const Name& name, const Protection& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...}, protection{protection} {}

    template <typename... V, typename... Args>
        requires type_is_possible<Protection, V...>
    Protecting_(const Name& name, const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          protection{std::get_if<Protection>(&protection)
                         ? std::get<Protection>(protection)
                         : Protection{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<Protection, V...>
    Protecting_(const Name& name, [[maybe_unused]] const std::variant<V...>& protection, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    auto& getProtection() & {
        return protection;
    }

    const auto& getProtection() const& {
        return protection;
    }

private:
    Protection protection{};
};

namespace Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, impl::Protecting_<T>>;

template <typename T>
struct DefendStrategy_<impl::Protecting_<T>> : DefendStrategy_<T> {};  // forward eventualy implemented strategy
