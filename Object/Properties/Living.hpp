#pragma once
#include <boost/mp11.hpp>
#include "Object/Concepts/Types/Name.hpp"
#include "Object/Strategies/AliveStrategy.hpp"
#include "Helpers/PropertyData.hpp"

namespace impl {
constexpr char living_type_name[] = "Living";

template <typename T>
struct Living_ : T {
    using property_data = PropertyData<living_type_name, Living_, T>;

    Living_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Health, INFO...> and sizeof...(INFO) > 0)
    Living_(const Name& name, std::tuple<INFO...>&& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::move(std::make_from_tuple<Health>(std::forward<decltype(hp)>(hp)))} {}

    Living_(const Name& name)
        : T{name} {}

    Living_(const Name& name, [[maybe_unused]] decltype(std::ignore) hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Living_(const Name& name, Health&& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::move(hp)} {}

    Living_(const Name& name, const Health& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{hp} {}

    template <typename... V>
        requires boost::mp11::mp_contains<std::variant<V...>, Health>::value
    Living_(const Name& name, const std::variant<V...>& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, hp{std::get<Health>(hp)} {}

    template <typename... V>
        requires(not boost::mp11::mp_contains<std::variant<V...>, Health>::value)
    Living_(const Name& name, [[maybe_unused]] const std::variant<V...>& hp, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

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
