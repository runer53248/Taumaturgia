#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"

namespace impl {

// MARK: WearingSimple_

template <typename T>
class WearingSimple_ : public T {
public:
    using property_data = PropertyData<WearingSimple_, T>;
    using hold_type = WearContainer;

    WearingSimple_() = default;

    template <typename... INFO, typename... Args>
    WearingSimple_(const Name& name, std::tuple<INFO...>&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::make_from_tuple<hold_type>(std::move(armorWear))} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create WearContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
    WearingSimple_(const Name& name, const std::tuple<INFO...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::make_from_tuple<hold_type>(armorWear)} {
        static_assert(constructible_from_args<hold_type, INFO...>, "Can't create WearContainer from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    WearingSimple_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit WearingSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    WearingSimple_(const Name& name)
        : T{name} {}

    template <typename... Args>
    WearingSimple_(const Name& name, [[maybe_unused]] decltype(std::ignore) armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    WearingSimple_(const Name& name, hold_type&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear_{std::move(armorWear)} {}

    template <typename... Args>
    WearingSimple_(const Name& name, const hold_type& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear_{armorWear} {}

    template <typename... V, typename... Args>
        requires contains_type<hold_type, V...>
    WearingSimple_(const Name& name, const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::get_if<hold_type>(&armorWear)
                         ? std::get<hold_type>(armorWear)
                         : hold_type{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<hold_type, V...>
    WearingSimple_(const Name& name, [[maybe_unused]] const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    WearingSimple_(hold_type&& armorWear, Args&&... args)
        : T{std::forward<Args>(args)...}, armorWear_{std::move(armorWear)} {}

    // MARK: getArmorWear

    constexpr auto& getArmorWear(this auto& self) {
        return self.armorWear_;
    }

private:
    hold_type armorWear_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
