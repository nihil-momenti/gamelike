#include "tile.hpp"

#include <algorithm>

static const double M_R3   = 1.73205081; // sqrt(3)
static const double M_R3_2 = 0.866025403784439; // sqrt(3) / 2

Tile_iterator::Tile_iterator(t_type *tile, int index)
    : type(BLOCK_TILE_ITERATOR), tile(tile), index(index) {
};

Tile::Tile() {
    tiles = new Tile[7];
}

Tile::Tile(int layer, double x, double z)
    : layer(layer), x(x), z(z) {
    if (layer == 0) {
    } else {
        tiles = new Tile[7];
        tiles[0] = Tile(layer - 1, x, z);
        tiles[1] = Tile(layer - 1, x + 0,           z + M_R3   * layer);
        tiles[2] = Tile(layer - 1, x + 1.5 * layer, z + M_R3_2 * layer);
        tiles[3] = Tile(layer - 1, x + 1.5 * layer, z - M_R3_2 * layer);
        tiles[4] = Tile(layer - 1, x + 0,           z - M_R3   * layer);
        tiles[5] = Tile(layer - 1, x - 1.5 * layer, z - M_R3_2 * layer);
        tiles[6] = Tile(layer - 1, x - 1.5 * layer, z + M_R3_2 * layer);
    }
}

Tile::Tile(const Tile &other) {
    layer = other.layer;
    x = other.x;
    z = other.z;
    tiles = new Tile[7];
    std::copy(&other.tiles[0], &other.tiles[6], &tiles[0]);
}

Tile::~Tile() {
    delete[] tiles;
}

Tile & Tile::operator= (const Tile &other) {
    layer = other.layer;
    x = other.x;
    z = other.z;
    std::copy(&other.tiles[0], &other.tiles[6], &tiles[0]);
    return *this;
}

Tile::iterator Tile::begin() {
    if (layer == 0) {
        return Tile::iterator(this, 0, BLOCK_TILE_ITERATOR);
    } else {
        return Tile::iterator(this, 0, TILE_TILE_ITERATOR);
    }
}

Tile::iterator Tile::end() {
    if (layer == 0) {
        return Tile::iterator(this, 7, BLOCK_TILE_ITERATOR);
    } else {
        return Tile::iterator(this, 7, TILE_TILE_ITERATOR);
    }
}
