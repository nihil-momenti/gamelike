#include "chunk.hpp"

#include <iostream>

#include <cstdlib>
#include <cmath>

Chunk::Chunk() {
    //for (Chunk::iterator it = this->begin(); it != this->end(); it++) {
    //    BlockWrapper bw = *it;
    for (BlockWrapper bw : (*this)) {
        //std::cout << "Created hex [" << bw.i << ", " << bw.j << ", " << bw.k << ", (" << bw.y << ")]." << std::endl;
        if (rand() % 3 < 1.0) {
            bw.block.type = 1;
        } else {
            bw.block.type = 0;
        }
    }
}

Chunk::iterator Chunk::begin() {
    return Chunk::iterator(this);
}

Chunk::iterator Chunk::end() {
    return Chunk::iterator(this, 0);
}
