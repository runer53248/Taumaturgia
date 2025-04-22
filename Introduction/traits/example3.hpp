#pragma once
#include "Taumaturgia/Traits/Helpers/CustomAccessType.hpp"

class Name;

struct CustomName_3 {  // struct without Name member
    auto name() & { return Name{"t_custom_name"}; }
    auto name() const& { return Name{"const t_custom_name"}; }
};

template <typename T>
    requires requires(T t) {
        { t.name() } -> std::same_as<Name>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};
