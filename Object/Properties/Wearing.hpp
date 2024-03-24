#pragma once
#include <boost/mp11.hpp>
#include "Helpers/PropertyData.hpp"
#include "Helpers/constructible_from_args.hpp"
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/WearStrategy.hpp"

namespace impl {
constinit char wearing_type_name[] = "Wearing";

template <typename T>
struct Wearing_ : T {
    using property_data = PropertyData<wearing_type_name, Wearing_, T>;

    Wearing_() = default;

    template <typename... INFO, typename... Args>
    Wearing_(const Name& name, std::tuple<INFO...>&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear{std::make_from_tuple<WearContainer>(std::move(armorWear))} {}

    template <typename... INFO, typename... Args>
    Wearing_(const Name& name, const std::tuple<INFO...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear{std::make_from_tuple<WearContainer>(armorWear)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<WearContainer, INFO...>)
    Wearing_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create WearContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<WearContainer, INFO...>)
    Wearing_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create WearContainer from given tuple.");
    }

    Wearing_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Wearing_(const Name& name, [[maybe_unused]] decltype(std::ignore) armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Wearing_(const Name& name, WearContainer&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear{std::move(armorWear)} {}

    template <typename... Args>
    Wearing_(const Name& name, const WearContainer& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear{armorWear} {}

    template <typename... V, typename... Args>
        requires boost::mp11::mp_contains<std::variant<V...>, WearContainer>::value
    Wearing_(const Name& name, const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear{std::get<WearContainer>(armorWear)} {}

    template <typename... V, typename... Args>
        requires(not boost::mp11::mp_contains<std::variant<V...>, WearContainer>::value)
    Wearing_(const Name& name, [[maybe_unused]] const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    auto& getArmorWear() & {
        return armorWear;
    }

    const auto& getArmorWear() const& {
        return armorWear;
    }

private:
    WearContainer armorWear{};
};

namespace Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Wearing = std::conditional_t<Wearingable<T>, T, impl::Wearing_<T>>;

template <typename T>
struct WearStrategy_<impl::Wearing_<T>> : WearStrategy_<T> {};  // forward eventualy implemented strategy
