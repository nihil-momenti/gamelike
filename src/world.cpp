#include "world.hpp"

World::World() {
    chunks.push_back(new Chunk(0,0,0,0));
    chunks.push_back(new Chunk(1,0,0,0));
    chunks.push_back(new Chunk(0,1,0,0));
    chunks.push_back(new Chunk(0,0,1,0));
    chunks.push_back(new Chunk(0,0,0,0));
    chunks.push_back(new Chunk(1,1,1,1));
}

World::~World() {
    for (Chunk *chunk : chunks) {
        delete chunk;
    }
    chunks.clear();
}
