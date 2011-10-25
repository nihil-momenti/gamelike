#pragma once

#include "block.hpp"

enum Tile_iterator_type {
    BLOCK_TILE_ITERATOR;
    TILE_TILE_ITERATOR;
};

template <typename T>
class Tile_iterator {
    public:
        typedef t_type T;
        Tile_iterator(t_type *, int);
        Tile_iterator(t_type *, Tile_iterator);

    private:
        int index;
        t_type *tile;
        Tile_iterator it;
        Tile_iterator end;
        Tile_iterator_type type;
};

class Tile {
    public:
        typedef Tile_iterator<Tile> iterator;
        Tile();
        Tile(int, double, double);
        Tile(const Tile &);
        ~Tile();

        Tile & operator= (const Tile &);

        iterator begin();
        iterator end();

    private:
        Tile *tiles;
        Block block;
        int layer;
        double x, z;
};

