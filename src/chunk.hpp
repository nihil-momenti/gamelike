#pragma once

#include <algorithm>

#include "block.hpp"
#include "chunk_iterator.hpp"

static const int CHUNK_SIZE = 8;
static const int CHUNK_HEIGHT = 16;

class Chunk {
    public:
        typedef ChunkIterator iterator;

        Chunk(int, int, int, int);
        ~Chunk();

        iterator begin();
        iterator end();

        int i, j, k, y;

    private:
        // 1 + 6 + 2*6 + 3*6 + ... * n*6
        Block *blocks;

        friend ChunkIterator;
};
