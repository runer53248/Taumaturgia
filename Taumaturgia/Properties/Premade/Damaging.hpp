#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Traits/DamageTraits.hpp"
#include "Taumaturgia/Types/Damage.hpp"
#include "Taumaturgia/Types/Name.hpp"

namespace impl {
inline constinit const char damaging_type_name[] = "Damaging";

template <typename T>
class Damaging_ : public T {
public:
    using property_data = PropertyData<damaging_type_name, Damaging_, T>;

    Damaging_() = default;

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, std::tuple<INFO...>&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<Damage>(std::move(dmg))} {
    }

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, const std::tuple<INFO...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<Damage>(dmg)} {
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
        : T{name, std::forward<Args>(args)...}, dmg_{std::move(dmg)} {}

    template <typename... Args>
    Damaging_(const Name& name, const Damage& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg_{dmg} {}

    template <typename... V, typename... Args>
        requires type_is_possible<Damage, V...>
    Damaging_(const Name& name, const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::get_if<Damage>(&dmg)
                   ? std::get<Damage>(dmg)
                   : Damage{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<Damage, V...>
    Damaging_(const Name& name, [[maybe_unused]] const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    auto& getDamage() & {
        return dmg_;
    }

    const auto& getDamage() const& {
        return dmg_;
    }

private:
    Damage dmg_{};
};

namespace Test {
struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Damaging = std::conditional_t<Damagingable<T>, T, impl::Damaging_<T>>;
