#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Concepts/Damagingable.hpp"
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Types/Name.hpp"

namespace impl {
inline constinit char damaging_type_name[] = "Damaging";

template <typename T>
struct Damaging_ : T {
    using property_data = PropertyData<damaging_type_name, Damaging_, T>;

    Damaging_() = default;

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, std::tuple<INFO...>&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg{std::make_from_tuple<Damage>(std::move(dmg))} {
    }

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, const std::tuple<INFO...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg{std::make_from_tuple<Damage>(dmg)} {
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Damage, INFO...>)
    Damaging_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create Damage from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Damage, INFO...>)
    Damaging_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create Damage from given tuple.");
    }

    Damaging_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Damaging_(const Name& name, [[maybe_unused]] decltype(std::ignore) dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Damaging_(const Name& name, Damage&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg{std::move(dmg)} {}

    template <typename... Args>
    Damaging_(const Name& name, const Damage& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg{dmg} {}

    template <typename... V, typename... Args>
        requires type_is_possible<Damage, V...>
    Damaging_(const Name& name, const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg{std::get_if<Damage>(&dmg)
                  ? std::get<Damage>(dmg)
                  : Damage{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<Damage, V...>
    Damaging_(const Name& name, [[maybe_unused]] const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

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
