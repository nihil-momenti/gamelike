#pragma once

#include "GL_bindings.hpp"
#include "chunk.hpp"

struct ChunkView {
    Chunk *chunk;

    ChunkView(Chunk *chunk);

    GLuint list;

    void gl_init();
    void display();
};
