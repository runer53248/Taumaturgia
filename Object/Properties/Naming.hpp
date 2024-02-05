#pragma once
#include "../Concepts/Namingable.hpp"
#include "PropertyData.hpp"

namespace impl {
constexpr char naming_type_name[] = "Naming";

template <typename T>
struct Naming_ : T {
    using property_data = PropertyData<naming_type_name, Naming_, T>;

    Naming_() = default;

    Naming_(const Name& name, auto&&... args)
        : T{std::forward<decltype(args)>(args)...}, name{name} {}

    auto& getName() & {
        return name;
    }

    const auto& getName() const& {
        return name;
    }

private:
    Name name{};
};

namespace Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
