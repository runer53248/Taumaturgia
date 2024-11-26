#pragma once

#include "Tile.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "Empty.hpp"

#ifndef IGNORE_ORDER_LIST
using LivingTile = add_properties_ordered<
    Tile,
    Living>;
#else 
using LivingTile = add_properties_unordered<
    Tile,
    Living>;
#endif

#else

struct LivingTile : Tile {
    Health hp;
};

#endif

static_assert(Gettingable<LivingTile>);

// TODO : check this
// ! if IGNORE_ORDER_LIST is defined then next assertions fails because
// ! custom strategies of Tile uses concept like:  requires std::is_base_of_v<Tile, T>
// ! then
// ! Tile = Naming_<Damaging_<Empty<void>>> 
// ! LivingTile = Naming_<Damaging_<Living_<Empty<void>>> 

// static_assert(is_custom_get_strategy<LivingTile>);
// static_assert(is_custom_alive_strategy<LivingTile>);
