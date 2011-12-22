#pragma once

#include "chunk.hpp"

#include <vector>

struct World {
    std::vector<Chunk*> chunks;

    World();
    ~World();
};
