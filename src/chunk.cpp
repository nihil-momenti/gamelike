#include "chunk.hpp"

#include <iostream>

#include <cstdlib>

Chunk::Chunk() {
    for (int i = -CHUNK_SIZE; i <= CHUNK_SIZE; i++) {
        for (int j = -CHUNK_SIZE + abs(i); j <= CHUNK_SIZE - abs(i); j++) {
            for (int k = -CHUNK_SIZE + abs(i) + abs(j); k <= CHUNK_SIZE - abs(i) - abs(j); k++) {
                std::cout << "Created hex [" << i << ", " << j << ", " << k << "]." << std::endl;
                if (rand() % 2 < 1.0) {
                    (*this)(i, j, k, 0).type = 1;
                } else {
                    (*this)(i, j, k, 0).type = 1;
                }
            }
        }
    }
}

Block & Chunk::operator() (int i, int j, int k, int y) {
    if (abs(i)+abs(j)+abs(k) > CHUNK_SIZE) {
        std::cout << "Invalid hex coord [" << i << ", " << j << ", " << k << "]." << std::endl;
        exit(87);
    }

    return blocks[((((y * CHUNK_HEIGHT) + k) * CHUNK_SIZE + j) * CHUNK_SIZE) + i];
}
