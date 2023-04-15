#pragma once
#include "../Concepts/Namingable.hpp"
#include "../Strategies/AliveStrategy.hpp"

template <typename T>
struct Living_: T {
	Living_(const Name& name, Hp hp, auto ...args): T{name, std::forward<decltype(args)>(args)...}, hp(hp) {}
	Living_(const Name& name, auto ...args): T{name, std::forward<decltype(args)>(args)...} {}

	Hp hp{};
};

struct Living_Test{};
static_assert(Livingable< Living_<Living_Test> >);

template <typename T>
using Living = std::conditional_t< Livingable<T>, T, Living_<T> >;
