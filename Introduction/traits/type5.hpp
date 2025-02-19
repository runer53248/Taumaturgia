#pragma once

struct Type5 {
    Name very_specific_name;
};

template <typename T>
    requires std::is_base_of_v<Type5, T>
struct traits::CustomAccessType<Name, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.very_specific_name);
    }
};
