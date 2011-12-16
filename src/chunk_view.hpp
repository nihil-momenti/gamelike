#pragma once

#include "chunk.hpp"

struct ChunkView {
    Chunk &chunk;

    ChunkView(Chunk &chunk);

    void gl_init();
    void display();
};
