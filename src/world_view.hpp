#pragma once

#include "world.hpp"

#include "chunk_view.hpp"

#include <SDL.h>

struct WorldView {
    World *world;
    ChunkView chunkView;

    WorldView(World *world);

    void gl_init();
    void display();
};
