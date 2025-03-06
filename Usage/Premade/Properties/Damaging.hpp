#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "buildin_defaults.hpp"

namespace impl {
inline constinit const char damaging_type_name[] = "Damaging";

template <typename T, typename... Tags>
class Damaging_;

template <typename... Tags>
struct PropertyFor<Damage, Tags...> {
    template <typename TARGET>
    using type = Damaging_<TARGET, Tags...>;
};

template <typename T, typename... Tags>
class Damaging_ : public T {
public:
    using property_data = PropertyData<damaging_type_name,
                                       PropertyFor<Damage, Tags...>::template type,
                                       T,
                                       Tags...>;
    using hold_type = Damage;

    // MARK: default C-tor

    Damaging_() = default;

    // MARK: tuple C-tors

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, std::tuple<INFO...>&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<Damage>(std::move(dmg))} {
        static_assert(constructible_from_args<Damage, INFO...>, "Can't create Damage from given tuple.");
    }

    template <typename... INFO, typename... Args>
    Damaging_(const Name& name, const std::tuple<INFO...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<Damage>(dmg)} {
        static_assert(constructible_from_args<Damage, INFO...>, "Can't create Damage from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Damaging_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename Arg>
        requires(std::derived_from<T, std::remove_cvref_t<Arg>>)
    explicit Damaging_(Arg&& t)
        : T{std::forward<Arg>(t)} {}

    // MARK: ignore and skip C-tors

    Damaging_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Damaging_(const Name& name, [[maybe_unused]] decltype(std::ignore) dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: type C-tors

    template <typename... Args>
    Damaging_(const Name& name, Damage&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg_{std::move(dmg)} {}

    template <typename... Args>
    Damaging_(const Name& name, const Damage& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg_{dmg} {}

    // MARK: variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<Damage, V...>
    Damaging_(const Name& name, const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::get_if<Damage>(&dmg)
                   ? std::get<Damage>(dmg)
                   : Damage{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<Damage, V...>
    Damaging_(const Name& name, [[maybe_unused]] const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    Damaging_(Damage&& dmg, Args&&... args)
        : T{std::forward<Args>(args)...}, dmg_{std::move(dmg)} {}

    // MARK: getDamage

    constexpr auto& getDamage(this auto& self) {
        return self.dmg_;
    }

private:
    Damage dmg_ = buildin_defaults<Damage>::get();
};

}  // namespace impl

namespace impl::Test {
struct Damaging_Test {};
static_assert(Damagingable<Damaging_<Damaging_Test>>);
static_assert(Damagingable<Damaging_<tag>>);
}  // namespace impl::Test

template <typename T, typename... Tags>
using Damaging = std::conditional_t<Damagingable<T>, T, impl::Damaging_<T, Tags...>>;
