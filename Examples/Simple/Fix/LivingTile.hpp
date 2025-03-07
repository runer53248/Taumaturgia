#pragma once
#include "Empty.hpp"
#include "Tile.hpp"

#ifndef IGNORE_ORDER_LIST
using LivingTileBuild = add_properties_ordered<
    Tile,
    Living>;
#else
using LivingTileBuild = add_properties_unordered<
    Tile,
    Living>;
#endif

struct LivingTileClass : Tile {
    Health hp;
};

#ifdef WITH_ADD_PROPERTIES
using LivingTile = LivingTileBuild;
#else
using LivingTile = LivingTileClass;
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
