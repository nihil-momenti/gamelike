#include "world.hpp"

World World::gen_random() {
    World w;
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            w.loaded_chunks.push_back(Chunk::gen_random(i,j,0));
        }
    }
    return w;
}
