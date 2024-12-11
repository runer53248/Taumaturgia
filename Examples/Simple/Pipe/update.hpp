#pragma once
#include <boost/mp11.hpp>
#include <type_traits>
#include "Taumaturgia/Properties/Helpers/taged_list.hpp"
#include "Taumaturgia/Traits/trait.hpp"

// update rest of target parameters
auto update = [](auto& target) {
    using boost::mp11::mp_unique;
    using std::remove_cvref_t;
    using std::same_as;

    return [&target]<typename... Args>
        requires(
            (same_as<mp_unique<list<remove_cvref_t<Args>...>>, list<remove_cvref_t<Args>...>>) and  // every argument have unique type
            (trait_accessable<remove_cvref_t<decltype(target)>, remove_cvref_t<Args>> and ...))     // every type is accessable by trait
    (Args&&... args) {
        ((trait<remove_cvref_t<Args>>::get(target) = std::forward<Args>(args)), ...);
    };
};
