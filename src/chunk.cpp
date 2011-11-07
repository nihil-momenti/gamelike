#include "chunk.hpp"

#include <iostream>

#include <cstdlib>
#include <cmath>

void populate_block(Block &block, int i, int j, int k, int y) {
    std::cout << "Created hex [" << i << ", " << j << ", " << k << ", (" << y << ")]." << std::endl;
    if (rand() % 3 < 1.0) {
        block.type = 1;
    } else {
        block.type = 0;
    }
}

Chunk::Chunk() {
    this->each(populate_block);
}

static inline int convert(int i, int j, int k, int y) {
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

    return 1 + 3*(n-1)*n + offset + y * 3 * CHUNK_SIZE * (CHUNK_SIZE + 1);
}

Block & Chunk::operator() (int i, int j, int k, int y) {
    if (abs(i)+abs(j)+abs(k) > CHUNK_SIZE) {
        std::cout << "Invalid hex coord [" << i << ", " << j << ", " << k << ", (" << y << ")]." << std::endl;
        exit(87);
    }
    if (convert(i, j, k, y) >= (1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT || convert(i, j, k, y) < 0) {
        std::cout << "Invalid hex coord [" << i << ", " << j << ", " << k << ", (" << y << ")]." << std::endl;
        std::cout << "Array index [" << convert(i, j, k, y) << "] out of [" << (1 + 3*CHUNK_SIZE*(CHUNK_SIZE+1))*CHUNK_HEIGHT << "]." << std::endl;
        exit(87);
    }

    return blocks[convert(i, j, k, y)];
}

void Chunk::each(BlockCallback callback) {
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        callback((*this)(0, 0, 0, y), 0, 0, 0, y);

        for (int n = 0; n <= CHUNK_SIZE; n++) {
            int i = n;
            int j = 0;
            int k = 0;

            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                i -= 1;
                j += 1;
            }
            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                j -= 1;
                k += 1;
            }
            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                k -= 1;
                i -= 1;
            }
            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                i += 1;
                j -= 1;
            }
            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                j += 1;
                k -= 1;
            }
            for (int l = n; l > 0; l--) {
                callback((*this)(i, j, k, y), i, j, k, y);
                k += 1;
                i += 1;
            }
        }
    }
}
