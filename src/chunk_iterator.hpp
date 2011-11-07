#pragma once

#include "block_wrapper.hpp"

class Chunk;

class ChunkIterator {
    public:
        ChunkIterator(Chunk *);
        ChunkIterator(Chunk *, int);

        bool operator== (const ChunkIterator &);
        bool operator!= (const ChunkIterator &);

        ChunkIterator & operator++ ();
        ChunkIterator & operator++ (int);
        BlockWrapper operator* ();

    private:
        Chunk *chunk;

        int i, j, k, y, n, side, l, index;
};

#include "chunk.hpp"
