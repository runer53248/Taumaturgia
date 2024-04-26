#pragma once
#include "Taumaturgia/Traits/NameTraits.hpp"
#include "Taumaturgia/Properties/Helpers/PropertyData.hpp"

namespace impl {
inline constinit const char naming_type_name[] = "Naming";

template <typename T>
class Naming_ : public T {
public:
    using property_data = PropertyData<naming_type_name, Naming_, T>;

    Naming_() = default;

template <typename... Args>
    Naming_(const Name& name, Args&&... args)
        : T{std::forward<Args>(args)...}, name_{name} {}

    auto& getName() & {
        return name_;
    }

    const auto& getName() const& {
        return name_;
    }

private:
    Name name_{};
};

namespace Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace Test

}  // namespace impl

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
