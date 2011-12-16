#include "chunk.hpp"

#include <iostream>

#include <cstdlib>
#include <cmath>

Chunk::Chunk() {
    blocks = new Block[(1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT];
    for (BlockWrapper bw : (*this)) {
        std::cout << "Created hex [" << bw.i << ", " << bw.j << ", " << bw.k << ", (" << bw.y << ")] at index [" << bw.index << "]." << std::endl;
        bw.block.type = int(rand() % 5);
    }
}

Chunk::~Chunk() {
    delete[] blocks;
}

Chunk::iterator Chunk::begin() {
    return Chunk::iterator(this);
}

Chunk::iterator Chunk::end() {
    return Chunk::iterator(this, 0);
}
