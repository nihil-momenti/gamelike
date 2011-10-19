#include "world.hpp"

World World::gen_random() {
    World w;
    for (int i = -5; i < 6; i++) {
        for (int j = -5; j < 6; j++) {
            w.loaded_chunks.push_back(Chunk::gen_random(i,j,0));
        }
    }
    return w;
}
