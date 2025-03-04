#pragma once
#include "Taumaturgia/Traits/trait.hpp"
#include "Usage/Types/Name/NameConcepts.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Name, name, Name);
#else
struct accessName : public impl::accessType<Name, std::string> {
    template <typename T>
    static const bool accessable = helpers::trait_access_convertable<T, accessName, std::string>;

    template <NameAccessable T>
        requires(not accessType<Name, std::string>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return (el.name);
    }

    template <GetNameAccessable T>
        requires(not accessType<Name, std::string>::accessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    using accessType<Name, std::string>::get;
};
#endif

}  // namespace traits

template <>
struct trait_<Name> {
    using type = traits::accessName;
};
