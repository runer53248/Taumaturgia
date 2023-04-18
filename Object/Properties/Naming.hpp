#pragma once
#include "../Concepts/Namingable.hpp"

template <typename T>
struct Naming_ : T {
    Naming_(const Name& name, auto... args)
        : T{std::forward<decltype(args)>(args)...}, name{name} {}

    Name name{};
};

struct Naming_Test {};
static_assert(Namingable<Naming_<Naming_Test> >);

template <typename T>
using Naming = std::conditional_t<Namingable<T>, T, Naming_<T> >;
