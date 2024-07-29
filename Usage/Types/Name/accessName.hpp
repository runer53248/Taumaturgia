#pragma once
#include "Usage/Types/Name/NameConcepts.hpp"

#include "Taumaturgia/Traits/accessType.hpp"

namespace traits {

#ifdef ACCESS_TRAIT_MACRO
CreateAccessTrait(Name, name, Name);
#else
struct accessName : public accessType<Name, std::string> {
    template <typename T>
    static const bool accessable = helpers::trait_access_convertable<T, accessName, std::string>;

    static constexpr auto& get(NameAccessable auto& el) noexcept {
        return el.name;
    }

    template <GetNameAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    using accessType<Name, std::string>::get;
};
#endif

}  // namespace traits
