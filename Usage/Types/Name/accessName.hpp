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
        requires(not(CustomNameAccessable<T> or GetTypeTemplateNameAccessable<T>))
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.getName();
    }

    template <CustomNameAccessable T>
        requires(not GetTypeTemplateNameAccessable<T>)
    static constexpr decltype(auto) get(T& el) noexcept {
        return CustomAccessName<std::remove_cvref_t<T> >::get(el);
    }

    template <GetTypeTemplateNameAccessable T>
    static constexpr decltype(auto) get(T& el) noexcept {
        return el.template getType<Name>();
    }

    using accessType<Name, std::string>::get;
};
#endif

}  // namespace traits
