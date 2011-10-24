#include "chunk.hpp"

#include <cstdlib>

Chunk Chunk::gen_random(int x, int y, int z) {
    Chunk c;
    c.x = x;
    c.y = y;
    c.z = z;

    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            for (int k = 0; k < CHUNK_HEIGHT; k++) {
                if (rand() < RAND_MAX / 2) {
                    c.blocks[i][j][k].block_type = 1;
                } else {
                    c.blocks[i][j][k].block_type = 0;
                }
            }
        }
    }

    return c;
}
