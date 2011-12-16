#pragma once

#include <algorithm>

#include "block.hpp"
#include "chunk_iterator.hpp"

static const int CHUNK_SIZE = 2;
static const int CHUNK_HEIGHT = 1;

class Chunk {
    public:
        typedef ChunkIterator iterator;

        Chunk();

        iterator begin();
        iterator end();

    private:
        // 1 + 6 + 2*6 + 3*6 + ... * n*6
        Block blocks[(1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT];

        friend ChunkIterator;
};
