#pragma once
#include <boost/mp11.hpp>
#include <variant>
#include "Taumaturgia/Properties/Helpers/constructible_from_args.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Usage/Types/Health/Health.hpp"
#include "Usage/Types/Name/Name.hpp"

namespace impl {
inline constinit const char living_type_name[] = "Living";

template <typename T>
class Living_ : public T {
public:
    using property_data = PropertyData<living_type_name, Living_, T>;

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

    // !

    template <typename... Args>
    Living_(const Token&, Args&&... args)
        : T{} {
        ((trait<Args>::get(*this) = std::forward<Args>(args)),...);
    }


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
