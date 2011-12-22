#pragma once

#include "world.hpp"

#include "chunk_view.hpp"

#include <SDL.h>
#include <vector>

struct WorldView {
    World *world;
    std::vector<ChunkView*> chunk_views;

    WorldView(World *world);
    ~WorldView();

    void gl_init();
    void display();
};
