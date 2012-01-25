static const double M_R3_2 = 0.866025403784439; // sqrt(3) / 2

#include "chunk_view.hpp"

#include "GL_bindings.hpp"

#include <algorithm>

static void draw_hexagonal_prism(float x, float y, float z, float height, float radius) {
    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius,      y + height / 2,     z                   );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x + radius,      y + height / 2,     z                   );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius,      y + height / 2,     z                   );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x - radius,      y + height / 2,     z                   );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x,               y + height / 2,     z                   );

    GL::Vertex3f(x - radius,      y - height / 2,     z                   );
    GL::Vertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x,               y - height / 2,     z                   );

    GL::Vertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x,               y - height / 2,     z                   );

    GL::Vertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius,      y - height / 2,     z                   );
    GL::Vertex3f(x,               y - height / 2,     z                   );

    GL::Vertex3f(x + radius,      y - height / 2,     z                   );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x,               y - height / 2,     z                   );

    GL::Vertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x,               y - height / 2,     z                   );

    GL::Vertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius,      y - height / 2,     z                   );
    GL::Vertex3f(x,               y - height / 2,     z                   );



    GL::Vertex3f(x - radius,      y - height / 2,     z                   );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius,      y + height / 2,     z                   );

    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius,      y - height / 2,     z                   );
    GL::Vertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );

    GL::Vertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );

    GL::Vertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );

    GL::Vertex3f(x + radius,      y - height / 2,     z                   );
    GL::Vertex3f(x + radius,      y + height / 2,     z                   );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );

    GL::Vertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    GL::Vertex3f(x + radius,      y - height / 2,     z                   );

    GL::Vertex3f(x - radius,      y - height / 2,     z                   );
    GL::Vertex3f(x - radius,      y + height / 2,     z                   );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );

    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius,      y - height / 2,     z                   );

    GL::Vertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );

    GL::Vertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );

    GL::Vertex3f(x + radius,      y - height / 2,     z                   );
    GL::Vertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius,      y + height / 2,     z                   );

    GL::Vertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    GL::Vertex3f(x + radius,      y - height / 2,     z                   );
    GL::Vertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
}
ChunkView::ChunkView(Chunk *chunk)
    : chunk(chunk) {
}

void ChunkView::gl_init() {
    list = GL::GenLists(1);
    GL::NewList(list, GL_COMPILE);
    GL::PushMatrix();
    GL::Translated((2*CHUNK_SIZE-2)*(chunk->i+0.5*(chunk->j-chunk->k))-.5*M_R3_2*(chunk->j+chunk->k), M_R3_2*CHUNK_HEIGHT*chunk->y, M_R3_2*(2*CHUNK_SIZE-2)*(chunk->j+chunk->k)-.5*(chunk->i+.5*(chunk->j-chunk->k)));
    GL::Begin(GL_TRIANGLES);
    for (Block &block : *chunk) {
        switch (block.type) {
            case 1:
                GL::Color3ub(150, 75, 0);
                break;
            case 2:
                GL::Color3ub(244, 164, 96);
                break;
            case 3:
                GL::Color3ub(23, 114, 69);
                break;
            case 4:
                GL::Color3ub(128, 128, 128);
                break;
        }

        if (block.type != 0) {
            draw_hexagonal_prism(M_R3_2*(block.j+block.k), M_R3_2*block.y, block.i+0.5*(block.j-block.k), M_R3_2, 0.5774);
        }
    }
    GL::End();
    GL::PopMatrix();
    GL::EndList();
}

void ChunkView::display() {
    GL::CallList(list);
}
