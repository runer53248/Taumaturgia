#pragma once
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Damage/Damage.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {

// MARK: DamagingSimple_

template <typename T, typename... Tags>
class DamagingSimple_ : public T {
public:
    using property_data = PropertyData<For<DamagingSimple_, Tags...>::template type, T, Tags...>;
    using hold_type = Damage;

    // MARK: default C-tor

    DamagingSimple_() = default;

    // MARK: tuple C-tors

    template <typename... INFO, typename... Args>
    DamagingSimple_(const Name& name, std::tuple<INFO...>&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<hold_type>(std::move(dmg))} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create Damage from given tuple.");
    }

    template <typename... INFO, typename... Args>
    DamagingSimple_(const Name& name, const std::tuple<INFO...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::make_from_tuple<hold_type>(dmg)} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create Damage from given tuple.");
    }

    // MARK: Unordered C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    DamagingSimple_(const Unordered&, Args&&... args)
        : T{} {
        auto fn = []<typename A>(auto* th, [[maybe_unused]] A& arg) {
            if constexpr (std::same_as<std::remove_cvref_t<A>, hold_type>) {
                th->getType() = std::forward<A>(arg);
            } else {
                if constexpr (requires { trait<std::remove_cvref_t<A>>::get(static_cast<T&>(*th)); }) {
                    trait<std::remove_cvref_t<A>>::get(static_cast<T&>(*th)) = std::forward<A>(arg);
                } else {
                    // static_assert(false, "Ambiguous get trait");
                }
            }
        };

        ((fn(this, args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename Arg>
        requires(std::derived_from<T, std::remove_cvref_t<Arg>>)
    explicit DamagingSimple_(Arg&& t)
        : T{std::forward<Arg>(t)} {}

    // MARK: ignore and skip C-tors

    DamagingSimple_(const Name& name)
        : T{name} {}

    template <typename... Args>
    DamagingSimple_(const Name& name, [[maybe_unused]] decltype(std::ignore) dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: type C-tors

    template <typename... Args>
    DamagingSimple_(const Name& name, hold_type&& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg_{std::move(dmg)} {}

    template <typename... Args>
    DamagingSimple_(const Name& name, const hold_type& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...}, dmg_{dmg} {}

    // MARK: variant C-tors

    template <typename... V, typename... Args>
        requires contains_type<hold_type, V...>
    DamagingSimple_(const Name& name, const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          dmg_{std::get_if<hold_type>(&dmg)
                   ? std::get<hold_type>(dmg)
                   : hold_type{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<hold_type, V...>
    DamagingSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& dmg, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: hold_type C-tor

    template <typename... Args>
    DamagingSimple_(hold_type&& dmg, Args&&... args)
        : T{std::forward<Args>(args)...}, dmg_{std::move(dmg)} {}

    template <typename... Args>
    DamagingSimple_(hold_type& dmg, Args&&... args)
        : T{std::forward<Args>(args)...}, dmg_{dmg} {}

    // MARK: getDamage

    constexpr auto& getDamage(this auto& self) {
        return self.dmg_;
    }

    constexpr auto& getType(this auto& self) {  //? this fix accessibility
        return self.dmg_;
    }

private:
    hold_type dmg_ = (boost::mp11::mp_empty<list<Tags...>>::value)
                         ? buildin_defaults<hold_type>::get()
                         : UserDefaultValue<hold_type, Tags...>::value();
};

}  // namespace impl
