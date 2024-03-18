#pragma once
#include <boost/mp11.hpp>
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/WearStrategy.hpp"
#include "Helpers/PropertyData.hpp"

namespace impl {
constexpr char wearing_type_name[] = "Wearing";

template <typename T>
struct Wearing_ : T {
    using property_data = PropertyData<wearing_type_name, Wearing_, T>;

    Wearing_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<WearContainer, INFO...> and sizeof...(INFO) > 0)
    Wearing_(const Name& name, std::tuple<INFO...>&& armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, armorWear{std::move(std::make_from_tuple<WearContainer>(std::forward<decltype(armorWear)>(armorWear)))} {}

    Wearing_(const Name& name)
        : T{name} {}

    Wearing_(const Name& name, [[maybe_unused]] decltype(std::ignore) armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Wearing_(const Name& name, WearContainer&& armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, armorWear{std::move(armorWear)} {}

    Wearing_(const Name& name, const WearContainer& armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, armorWear{armorWear} {}

    template <typename... V>
        requires boost::mp11::mp_contains<std::variant<V...>, WearContainer>::value
    Wearing_(const Name& name, const std::variant<V...>& armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, armorWear{std::get<WearContainer>(armorWear)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, WearContainer>::value)
    Wearing_(const Name& name, [[maybe_unused]] const std::variant<V...>& armorWear, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

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
