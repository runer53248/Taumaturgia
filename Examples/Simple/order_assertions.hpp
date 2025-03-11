#pragma once

namespace order_test {
using Tile_2 = add_properties_ordered<Empty,
                                      Naming,
                                      Damaging>;

static_assert(std::same_as<
              Tile,
              Tile_2>);

static_assert(std::same_as<
              Tile,
              Tile_list::apply_ordered_properties_to<Empty>>);
}  // namespace order_test

namespace unorder_test {
using Tile_unordered_2 = add_properties_unordered<Empty,
                                                  Naming,
                                                  Damaging>;
static_assert(std::same_as<
              Tile_unordered,
              Tile_unordered_2>);

static_assert(std::same_as<  // Tile is still ordered
              Tile,
              add_properties_unordered<Tile,
                                       Naming,
                                       Damaging>>);
static_assert(std::same_as<  // Tile is still ordered
              Tile,
              properties_list<>::apply_unordered_properties_to<Tile>>);

static_assert(std::same_as<  // Tile_unordered is still unordered
              Tile_unordered,
              add_properties_unordered<Tile_unordered,
                                       Damaging,
                                       Naming>>);
static_assert(std::same_as<  // Tile_unordered is still unordered
              Tile_unordered,
              properties_list<>::apply_unordered_properties_to<Tile_unordered>>);

static_assert(std::same_as<  // Tile_unordered is now ordered
              Tile,
              add_properties_ordered<Tile_unordered,
                                     Damaging,
                                     Naming>>);
static_assert(std::same_as<  // Tile_unordered is now ordered
              Tile,
              properties_list<>::apply_ordered_properties_to<Tile_unordered>>);

static_assert(std::same_as<
              Tile_list::apply_unordered_properties_to<Tile_unordered>,
              properties_list<>::apply_unordered_properties_to<Tile_unordered>>);
static_assert(std::same_as<
              Tile_list::apply_unordered_properties_to<Tile>,
              properties_list<>::apply_unordered_properties_to<Tile>>);
}  // namespace unorder_test

using unordered_type1 = add_properties_unordered<Empty,
                                                 Damaging,
                                                 Naming>;  // 2 - Naming
using unordered_type2 = add_properties_unordered<Empty,
                                                 Naming,  // 1 - Naming
                                                 Damaging>;
static_assert(not std::same_as<unordered_type1, unordered_type2>);
static_assert(std::same_as<
              unordered_type1,
              properties_list<>::apply_ordered_properties_to<unordered_type2>>);  // ordered version moves Naming at end
