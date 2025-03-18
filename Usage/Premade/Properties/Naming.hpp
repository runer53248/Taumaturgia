#pragma once
#include <boost/mp11.hpp>
#include "Features.hpp"
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"
#include "buildin_defaults.hpp"

// #include "Usage/Traits/accessName.hpp"

namespace impl {
inline constinit const char naming_type_name[] = "Naming";

template <typename T>
class NamingSimple_ : public T {
public:
    using property_data = PropertyData<naming_type_name, NamingSimple_, T>;
    using hold_type = Name;

    NamingSimple_() = default;

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>, list<std::remove_cvref_t<Args>...>>  // every argument have unique type
    NamingSimple_(const Token&, Args&&... args)
        : T{} {
        ((trait<std::remove_cvref_t<Args>>::get(*this) = std::forward<Args>(args)), ...);
    }

    // MARK: copy/move C-tors

    template <typename TT>
        requires(std::derived_from<T, std::remove_cvref_t<TT>>)
    explicit NamingSimple_(TT&& t)
        : T{std::forward<TT>(t)} {}

    template <typename... Args>
    NamingSimple_(const Name& name, Args&&... args)
        : T{std::forward<Args>(args)...}, name_{name} {}

    constexpr decltype(auto) getName(this auto& self) {
        return (self.name_);
    }

private:
    Name name_ = buildin_defaults<Name>::get();
};

template <typename T>
class Naming_ : public Features_<NamingSimple_<T>> {
public:
    using property_data = PropertyData<naming_type_name, Naming_, T>;
    using child = Features_<NamingSimple_<T>>;
    using typename child::hold_type;

    using child::child;
};

}  // namespace impl

namespace impl::Test {
struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test>>);
}  // namespace impl::Test

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, impl::Naming_<T>>;
