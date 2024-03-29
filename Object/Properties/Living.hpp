#pragma once
#include <boost/mp11.hpp>
#include "Helpers/PropertyData.hpp"
#include "Helpers/constructible_from_args.hpp"
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/AliveStrategy.hpp"

namespace impl {
constinit char living_type_name[] = "Living";

template <typename T>
struct Living_ : T {
    using property_data = PropertyData<living_type_name, Living_, T>;

    Living_() = default;

    template <typename... INFO, typename... Args>
    Living_(const Name& name, std::tuple<INFO...>&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          hp{std::make_from_tuple<Health>(std::move(hp))} {}

    template <typename... INFO, typename... Args>
    Living_(const Name& name, const std::tuple<INFO...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...},
          hp{std::make_from_tuple<Health>(hp)} {}

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Health, INFO...>)
    Living_(const Name&, std::tuple<INFO...>&&, Args&&...) {
        throw std::logic_error("Can't create Health from given tuple.");
    }

    template <typename... INFO, typename... Args>
        requires(not constructible_from_args<Health, INFO...>)
    Living_(const Name&, const std::tuple<INFO...>&, Args&&...) {
        throw std::logic_error("Can't create Health from given tuple.");
    }

    Living_(const Name& name)
        : T{name} {}

    template <typename... Args>
    Living_(const Name& name, [[maybe_unused]] decltype(std::ignore) hp, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    template <typename... Args>
    Living_(const Name& name, Health&& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp{std::move(hp)} {}

    template <typename... Args>
    Living_(const Name& name, const Health& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp{hp} {}

    template <typename... V, typename... Args>
        requires boost::mp11::mp_contains<std::variant<V...>, Health>::value
    Living_(const Name& name, const std::variant<V...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...}, hp{std::get<Health>(hp)} {}

    template <typename... V, typename... Args>
        requires(not boost::mp11::mp_contains<std::variant<V...>, Health>::value)
    Living_(const Name& name, [[maybe_unused]] const std::variant<V...>& hp, Args&&... args)
        : T{name, std::forward<Args>(args)...} {}

    auto& getHealth() & {
        return hp;
    }

    const auto& getHealth() const& {
        return hp;
    }

private:
    Health hp{};
};

namespace Test {
struct Living_Test {};
static_assert(Livingable<Living_<Living_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Living = std::conditional_t<Livingable<T>, T, impl::Living_<T>>;
