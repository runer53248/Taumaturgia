#pragma once
#include <boost/mp11.hpp>
#include "Taumaturgia/Properties/Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/UserDefaultValue.hpp"
#include "Taumaturgia/Properties/unordered_token.hpp"

namespace impl {

template <typename T>
class NamingSimple_ : public T {
public:
    using property_data = PropertyData<NamingSimple_, T>;
    using hold_type = Name;

    NamingSimple_() = default;

    // MARK: Token C-tors

    template <typename... Args>
        requires std::same_as<
            boost::mp11::mp_unique<list<std::remove_cvref_t<Args>...>>,
            list<std::remove_cvref_t<Args>...>>  // every argument have unique type
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
    NamingSimple_(const hold_type& name, Args&&... args)
        : T{std::forward<Args>(args)...}, name_{name} {}

    constexpr decltype(auto) getName(this auto& self) {
        return (self.name_);
    }

private:
    hold_type name_ = buildin_defaults<hold_type>::get();
};

}  // namespace impl
