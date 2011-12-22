#include "world.hpp"

World::World() {
    chunks.push_back(new Chunk());
}

World::~World() {
    for (Chunk *chunk : chunks) {
        delete chunk;
    }
    chunks.clear();
}
