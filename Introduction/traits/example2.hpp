#pragma once
#include "Taumaturgia/Traits/TypeConcepts.hpp"

class Name;

struct CustomName_2 {  // struct with custom Name getter
    decltype(auto) name(this auto& self) { return (self.name_); }

private:
    Name name_;
};

template <typename T>
    requires requires(T t) {
        { t.name() } -> std::same_as<Name&>;
    }
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.name());
    }
};
