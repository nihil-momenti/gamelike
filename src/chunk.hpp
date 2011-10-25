#pragma once

#include "block.hpp"

static const int CHUNK_SIZE = 16;
static const int CHUNK_HEIGHT = 16;

struct Chunk {
    Block blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
    int x, y, z;

    static Chunk gen_random(int,int,int);
};
