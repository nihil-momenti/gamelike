#include "chunk.hpp"

#include <iostream>

#include <cstdlib>
#include <cmath>

Chunk::Chunk() {
    //for (Chunk::iterator it = this->begin(); it != this->end(); it++) {
    //    BlockWrapper bw = *it;
    for (BlockWrapper bw : (*this)) {
        std::cout << "Created hex [" << bw.i << ", " << bw.j << ", " << bw.k << ", (" << bw.y << ")] at index [" << bw.index << "]." << std::endl;
        bw.block.type = int(rand() % 5);
    }
}

Chunk::iterator Chunk::begin() {
    return Chunk::iterator(this);
}

Chunk::iterator Chunk::end() {
    return Chunk::iterator(this, 0);
}
