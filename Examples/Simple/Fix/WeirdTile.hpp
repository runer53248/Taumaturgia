#pragma once

#include "Tile.hpp"
#include "Weird.hpp"

#ifdef WITH_ADD_PROPERTIES

#include "Empty.hpp"

using WeirdTile = add_properties_ordered<
    Tile,
    Weird>;

#else

struct WeirdTile : Tile {};

#endif

static_assert(Gettingable<WeirdTile>);

//TODO: add some alternative for is_base_of_v - something that check base and all of its properties  

// ! assertions false because new type edit order of Tile type
// ! custom strategies of Tile uses concept like:  requires std::is_base_of_v<Tile, T>
// ! and base was changed -> no longer count as Tile type

// static_assert(is_custom_get_strategy<WeirdTile>);    // !
// static_assert(is_custom_alive_strategy<WeirdTile>);  // !
