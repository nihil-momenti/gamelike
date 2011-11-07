#pragma once

#include "block.hpp"

static const int CHUNK_SIZE = 16;
static const int CHUNK_HEIGHT = 16;

typedef void (*BlockCallback)(Block &, int i, int j, int k, int y);

struct Chunk {
    // 1 + 6 + 2*6 + 3*6 + ... * n*6
    Block blocks[(1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT];

    Chunk();

    Block & operator() (int, int, int, int);

    void each(BlockCallback);
};
