#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"
#include "buildin_defaults.hpp"

namespace impl {
inline constinit const char wearing_type_name[] = "Wearing";

template <typename T>
class Wearing_ : public T {
public:
    using property_data = PropertyData<wearing_type_name, Wearing_, T>;
    using hold_type = WearContainer;

    Wearing_() = default;

    template <typename... INFO, typename... Args>
    Wearing_(const Name& name, std::tuple<INFO...>&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::make_from_tuple<WearContainer>(std::move(armorWear))} {
        static_assert(constructible_from_args<WearContainer, INFO...>, "Can't create WearContainer from given tuple.");
    }

    template <typename... INFO, typename... Args>
    Wearing_(const Name& name, const std::tuple<INFO...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::make_from_tuple<WearContainer>(armorWear)} {
        static_assert(constructible_from_args<WearContainer, INFO...>, "Can't create WearContainer from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Wearing_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit Wearing_(TT&& t)
        : T{std::forward<TT>(t)} {}

    Wearing_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Wearing_(const Name& name, [[maybe_unused]] decltype(std::ignore) armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Wearing_(const Name& name, WearContainer&& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear_{std::move(armorWear)} {}

    template <typename... Args>
    Wearing_(const Name& name, const WearContainer& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear_{armorWear} {}

    template <typename... V, typename... Args>
        requires contains_type<WearContainer, V...>
    Wearing_(const Name& name, const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::get_if<WearContainer>(&armorWear)
                         ? std::get<WearContainer>(armorWear)
                         : WearContainer{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<WearContainer, V...>
    Wearing_(const Name& name, [[maybe_unused]] const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    Wearing_(WearContainer&& armorWear, Args&&... args)
        : T{std::forward<Args>(args)...}, armorWear_{std::move(armorWear)} {}

    // MARK: getArmorWear

    constexpr auto& getArmorWear(this auto& self) {
        return self.armorWear_;
    }

private:
    WearContainer armorWear_ = buildin_defaults<WearContainer>::get();
};

}  // namespace impl

namespace impl::Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
}  // namespace impl::Test

template <typename T>
using Wearing = std::conditional_t<Wearingable<T>, T, impl::Wearing_<T>>;
