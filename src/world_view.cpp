#include "world_view.hpp"

WorldView::WorldView(World *world)
        : world(world) {
    for (Chunk *chunk : world->chunks) {
        chunk_views.push_back(new ChunkView(chunk));
    }
}

WorldView::~WorldView() {
    for (ChunkView *chunk_view : chunk_views) {
        delete chunk_view;
    }
    chunk_views.clear();
}

void WorldView::gl_init() {
    for (ChunkView *chunk_view : chunk_views) {
        chunk_view->gl_init();
    }

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    for (ChunkView *chunk_view : chunk_views) {
        chunk_view->display();
    }
    glEndList();
}

void WorldView::display() {
    glCallList(list);
}
