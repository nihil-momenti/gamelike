#pragma once

#include "world.hpp"

#include <SDL.h>

struct WorldView {
    World world;

    WorldView();
    WorldView(World world);

    void gl_init();
    void display();
};
