#pragma once
#include <boost/mp11.hpp>
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/AttackStrategy.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char damaging_type_name[] = "Damaging";

template <typename T>
struct Damaging_ : T {
    using property_data = PropertyData<damaging_type_name, Damaging_, T>;

    Damaging_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Damage, INFO...> and sizeof...(INFO) > 0)
    Damaging_(const Name& name, std::tuple<INFO...>&& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::move(std::make_from_tuple<Damage>(std::forward<decltype(dmg)>(dmg)))} {
    }

    Damaging_(const Name& name)
        : T{name} {}

    Damaging_(const Name& name, [[maybe_unused]] decltype(std::ignore) dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Damaging_(const Name& name, Damage&& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::move(dmg)} {}

    Damaging_(const Name& name, const Damage& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{dmg} {}

    template <typename... V>
        requires boost::mp11::mp_contains<std::variant<V...>, Damage>::value
    Damaging_(const Name& name, const std::variant<V...>& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, dmg{std::get<Damage>(dmg)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, Damage>::value)
    Damaging_(const Name& name, [[maybe_unused]] const std::variant<V...>& dmg, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    auto& getDamage() & {
        return dmg;
    }

    const auto& getDamage() const& {
        return dmg;
    }

private:
    Damage dmg{};
};

namespace Test {
struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Damaging = std::conditional_t<Damagingable<T>, T, impl::Damaging_<T>>;

template <typename T>
struct AttackStrategy_<impl::Damaging_<T>> : AttackStrategy_<T> {};  // forward eventualy implemented strategy
