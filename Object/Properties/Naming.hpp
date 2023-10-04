#pragma once
#include "../Concepts/Namingable.hpp"
#include "PropertyData.hpp"

constexpr char naming_type_name[] = "Naming";

template <typename T>
struct Naming_ : T {
    using property_data = PropertyData<Naming_, T, naming_type_name>;

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

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, Naming_<T>>;
