#include "world_view.hpp"

WorldView::WorldView(World *world)
    : world(world), chunkView(world->chunk)
{
}

void WorldView::gl_init() {
    chunkView.gl_init();
}

void WorldView::display() {
    chunkView.display();
}
