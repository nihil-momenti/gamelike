#include "world_view.hpp"

#include "GL_bindings.hpp"

static void draw_cube(float x1, float x2, float y1, float y2, float z1, float z2) {
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);

    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);

    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);

    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);

    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);

    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);

    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);

    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y1, z1);

    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);

    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x1, y1, z1);

    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);
    glVertex3f(x2, y2, z2);

    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
}

WorldView::WorldView() {
}

WorldView::WorldView(World world) 
    : world(world)
{
}

void WorldView::gl_init() {}

void WorldView::display() {
    glColor3f(0.59, 0.29, 0);
    glBegin(GL_TRIANGLES);
#if __cplusplus > 199711L
    for (const Chunk &chunk : world.loaded_chunks) {
#else
    for (std::vector<Chunk>::const_iterator it = world.loaded_chunks.begin(); it != world.loaded_chunks.end(); it++) {
        const Chunk &chunk = *it;
#endif
        for (int i = 0; i < CHUNK_SIZE; i++) {
            for (int j = 0; j < CHUNK_SIZE; j++) {
                for (int k = 0; k < CHUNK_HEIGHT; k++) {
                    const Block &block = chunk.blocks[i][j][k];
                    if (block.block_type == 1) {
                        draw_cube(
                                chunk.x * 10 + (i-0.5) / (float) CHUNK_SIZE * 10,
                                chunk.x * 10 + (i+0.5) / (float) CHUNK_SIZE * 10,
                                chunk.z * 10 + (k-0.5) / (float) CHUNK_HEIGHT * 10,
                                chunk.z * 10 + (k+0.5) / (float) CHUNK_HEIGHT * 10,
                                chunk.y * 10 + (j-0.5) / (float) CHUNK_SIZE * 10,
                                chunk.y * 10 + (j+0.5) / (float) CHUNK_SIZE * 10
                        );
                    }
                }
            }
        }
    }
    glEnd();
}
