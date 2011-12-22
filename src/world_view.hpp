#pragma once

#include "world.hpp"

#include "chunk_view.hpp"

#include "GL_bindings.hpp"

#include <vector>

struct WorldView {
    public:
        World *world;
        std::vector<ChunkView*> chunk_views;

        WorldView(World *world);
        ~WorldView();

        void gl_init();
        void display();
    private:
        GLuint list;
};
