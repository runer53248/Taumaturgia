#pragma once
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"

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

    constexpr auto& getName(this auto& self) {
        return self.name_;
    }

private:
    Name name_{};
};

}  // namespace impl

#ifdef WITH_ADD_PROPERTIES
#include "Taumaturgia/Traits/UserTypeTraits.hpp"
template <typename T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(GetNameAccessable auto& el) {
        return el.getName();
    }
};
#endif

namespace impl::Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace impl::Test

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
