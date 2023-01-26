#pragma once
#include "Object/Actions/Actions.hpp"
#include "Object/Classes/Classes.hpp"
#include "Object/ObjectModel.hpp"

template<> struct Attack<Weapon> : Attack<Accept> {}; // all Weapons can attack
template<> struct Defend<Armor> : Defend<Accept> {}; // all Armors can defend
template<> struct Defend<Helmet> : Defend<Accept> {}; // all Helmets can defend
