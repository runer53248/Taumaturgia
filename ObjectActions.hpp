#pragma once
#include "Object/Actions/Actions.hpp"
#include "Object/Classes/Classes.hpp"
#include "Object/ObjectModel.hpp"

template<> struct Attack<Weapon> : Attack<Accept> { // all Weapons can attack
	using Attack<Accept>::operator();
};

template<> struct Defend<Armor> : Defend<Accept> { // all Armors can defend
	using Defend<Accept>::operator();
};

template<> struct Defend<Helmet> : Defend<Accept> { // all Helmets can defend
	using Defend<Accept>::operator();
};
