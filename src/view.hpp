#pragma once

#include "camera.hpp"
#include "world_view.hpp"

class View {
    public:
        Camera camera;
        WorldView *world;

        View(int, int);

    private:
};
