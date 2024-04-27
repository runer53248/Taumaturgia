#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Traits/ArmorWearTraits.hpp"
#include "Taumaturgia/Types/Name.hpp"
#include "Taumaturgia/Types/WearContainer.hpp"

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
          armorWear_{std::make_from_tuple<WearContainer>(std::move(armorWear))} {}

    template <typename... INFO, typename... Args>
    Wearing_(const Name& name, const std::tuple<INFO...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::make_from_tuple<WearContainer>(armorWear)} {}

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
        : T{name, std::forward<Args>(args)...}, armorWear_{std::move(armorWear)} {}

    template <typename... Args>
    Wearing_(const Name& name, const WearContainer& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...}, armorWear_{armorWear} {}

    template <typename... V, typename... Args>
        requires type_is_possible<WearContainer, V...>
    Wearing_(const Name& name, const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          armorWear_{std::get_if<WearContainer>(&armorWear)
                         ? std::get<WearContainer>(armorWear)
                         : WearContainer{}} {}

    template <typename... V, typename... Args>
        requires type_is_not_possible<WearContainer, V...>
    Wearing_(const Name& name, [[maybe_unused]] const std::variant<V...>& armorWear, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    constexpr auto& getArmorWear() & {
        return armorWear_;
    }

    constexpr const auto& getArmorWear() const& {
        return armorWear_;
    }

private:
    WearContainer armorWear_{};
};

namespace Test {
struct Wearing_Test {};
static_assert(Wearingable<Wearing_<Wearing_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Wearing = std::conditional_t<Wearingable<T>, T, impl::Wearing_<T>>;
