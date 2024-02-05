#pragma once
#include "../Concepts/Types/Name.hpp"
#include "../Strategies/DefendStrategy.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char protecting_type_name[] = "Protecting";

template <typename T>
struct Protecting_ : T {
    using property_data = PropertyData<protecting_type_name, Protecting_, T>;

    Protecting_() = default;

    template <typename... INFO>
        requires(std::is_constructible_v<Protection, INFO...> and sizeof...(INFO) > 0)
    Protecting_(const Name& name, std::tuple<INFO...>&& protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, protection{std::move(std::make_from_tuple<Protection>(std::forward<decltype(protection)>(protection)))} {}

    Protecting_(const Name& name)
        : T{name} {}

    Protecting_(const Name& name, [[maybe_unused]] decltype(std::ignore) protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...} {}

    Protecting_(const Name& name, Protection&& protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, protection{std::move(protection)} {}

    Protecting_(const Name& name, const Protection& protection, auto&&... args)
        : T{name, std::forward<decltype(args)>(args)...}, protection{protection} {}

    auto& getProtection() & {
        return protection;
    }

    const auto& getProtection() const& {
        return protection;
    }

private:
    Protection protection{};
};

namespace Test {
struct Protecting_Test {};
static_assert(Protectingable<Protecting_<Protecting_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Protecting = std::conditional_t<Protectingable<T>, T, impl::Protecting_<T>>;

template <typename T>
struct DefendStrategy_<impl::Protecting_<T>> : DefendStrategy_<T> {};  // forward eventualy implemented strategy
