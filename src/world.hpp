#pragma once

#include "chunk.hpp"

#include <vector>

struct World {
    std::vector<Chunk> loaded_chunks;

    static World gen_random();
};
