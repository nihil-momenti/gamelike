#pragma once

#include "camera.hpp"
#include "world_view.hpp"

// TODO: proper OO camera implementation.
struct Camera1 {
    static void inline look(double interpolation) {
        Camera::look(interpolation);
    }
};

class View {
    public:
        Camera1 camera;
        WorldView *world;

        View();

    private:
};
