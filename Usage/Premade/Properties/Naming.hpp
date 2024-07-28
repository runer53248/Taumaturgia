#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/Token.hpp"

namespace impl {
inline constinit const char naming_type_name[] = "Naming";

template <typename T>
class Naming_ : public T {
public:
    using property_data = PropertyData<naming_type_name, Naming_, T>;

    template <typename TARGET>
    using apply = std::conditional_t<Namingable<TARGET>, TARGET, impl::Naming_<TARGET>>;

    Naming_() = default;

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    Naming_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit Naming_(TT&& t)
        : T{std::forward<TT>(t)} {}

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

namespace impl::Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace impl::Test

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
