#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Usage/Types/Name/Name.hpp"
#include "Usage/Types/WearContainer/WearContainer.hpp"
#include "Taumaturgia/Properties/Token.hpp"

namespace impl {
inline constinit const char wearing_type_name[] = "Wearing";

template <typename T>
class Wearing_ : public T {
public:
    using property_data = PropertyData<wearing_type_name, Wearing_, T>;

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

    // !

    template <typename... Args>
    Wearing_(const Token&, Args&&... args)
        : T{} {
        ((trait<Args>::get(*this) = std::forward<Args>(args)),...);
    }


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
    WearContainer armorWear_{};
};

}  // namespace impl

namespace impl::Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
}  // namespace impl::Test

template <typename T>
using Wearing = std::conditional_t<Wearingable<T>, T, impl::Wearing_<T>>;
