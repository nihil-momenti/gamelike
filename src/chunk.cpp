#include "chunk.hpp"

#include <iostream>

#include <cstdlib>
#include <cmath>

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

static int convert(int i, int j, int k) {
    int n = abs(i) + abs(j) + abs(k);

    int offset = 0;

    if (i > 0 && k == 0) {
        offset = + 0*n + j;
    } else if (j > 0 && i == 0) {
        offset = + 1*n + k;
    } else if (k > 0 && j == 0) {
        offset = + 2*n - i;
    } else if (i < 0 && k == 0) {
        offset = + 3*n - j;
    } else if (j < 0 && i == 0) {
        offset = + 4*n - k;
    } else if (k < 0 && j == 0) {
        offset = + 5*n + i;
    }

    return 1 + 3*(n-1)*n + offset;
}

Block & Chunk::operator() (int i, int j, int k, int y) {
    if (abs(i)+abs(j)+abs(k) > CHUNK_SIZE) {
        std::cout << "Invalid hex coord [" << i << ", " << j << ", " << k << "]." << std::endl;
        exit(87);
    }
    if (convert(i, j, k) >= (1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT || convert(i, j, k) < 0) {
        std::cout << "Invalid hex coord [" << i << ", " << j << ", " << k << "]." << std::endl;
        std::cout << "Array index [" << convert(i, j, k) << "] out of [" << (1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT << "]." << std::endl;
        exit(87);
    }

    return blocks[convert(i, j, k)];
}
