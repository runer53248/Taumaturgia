#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/Token.hpp"
#include "Usage/Types/Health/Health.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {
inline constinit const char living_type_name[] = "Living";

template <typename T>
class Living_ : public T {
public:
    using property_data = PropertyData<living_type_name, Living_, T>;

    template <typename TARGET>
    using apply = std::conditional_t<Livingable<TARGET>, TARGET, impl::Living_<TARGET>>;

    Living_() = default;

    template <typename... INFO, typename... Args>
    Living_(const Name& name, std::tuple<INFO...>&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          hp_{std::make_from_tuple<Health>(std::move(hp))} {
        static_assert(constructible_from_args<Health, INFO...>, "Can't create Health from given tuple.");
    }

    template <typename... INFO, typename... Args>
    Living_(const Name& name, const std::tuple<INFO...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          hp_{std::make_from_tuple<Health>(hp)} {
        static_assert(constructible_from_args<Health, INFO...>, "Can't create Health from given tuple.");
    }

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Living_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit Living_(TT&& t)
        : T{std::forward<TT>(t)} {}

    Living_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Living_(const Name& name, [[maybe_unused]] decltype(std::ignore) hp, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Living_(const Name& name, Health&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{std::move(hp)} {}

    template <typename... Args>
    Living_(const Name& name, const Health& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp_{hp} {}

    template <typename... V, typename... Args>
        requires contains_type<Health, V...>
    Living_(const Name& name, const std::variant<V...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          hp_{std::get_if<Health>(&hp)
                  ? std::get<Health>(hp)
                  : Health{}} {}

    template <typename... V, typename... Args>
        requires not_contains_type<Health, V...>
    Living_(const Name& name, [[maybe_unused]] const std::variant<V...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    // MARK: nameless C-tor

    template <typename... Args>
    Living_(Health&& hp, Args&&... args)
        : T{std::forward<Args>(args)...}, hp_{std::move(hp)} {}

    // MARK: getHealth

    constexpr auto& getHealth(this auto& self) {
        return self.hp_;
    }

private:
    Health hp_{};
};

}  // namespace impl

namespace impl::Test {
struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);
}  // namespace impl::Test

template <typename T>
using Living = std::conditional_t<Livingable<T>, T, impl::Living_<T>>;
