#pragma once
#include "Actions/Battle.hpp"
#include "Actions/Cure.hpp"
#include "Actions/Protection.hpp"

#include "Classes/Armor.hpp"
#include "Classes/Helmet.hpp"
#include "Classes/Potion.hpp"
#include "Classes/Scroll.hpp"
#include "Classes/Weapon.hpp"

#include "ObjectModel.hpp"

template<> struct Object::Attack<Weapon> : Object::Attack<Accept> { // all Weapons can attack
	using Object::Attack<Accept>::operator();
};

template<> struct Object::Defend<Armor> : Object::Defend<Accept> { // all Armors can defend
	using Object::Defend<Accept>::operator();
};

template<> struct Object::Defend<Helmet> : Object::Defend<Accept> { // all Helmets can defend
	using Object::Defend<Accept>::operator();
};
