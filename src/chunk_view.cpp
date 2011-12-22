static const double M_R3_2 = 0.866025403784439; // sqrt(3) / 2

#include "chunk_view.hpp"

#include "GL_bindings.hpp"

#include <algorithm>

static void draw_hexagonal_prism(float x, float y, float z, float height, float radius) {
    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius,      y + height / 2,     z                   );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x + radius,      y + height / 2,     z                   );
    glVertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius,      y + height / 2,     z                   );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x - radius,      y + height / 2,     z                   );
    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x,               y + height / 2,     z                   );

    glVertex3f(x - radius,      y - height / 2,     z                   );
    glVertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x,               y - height / 2,     z                   );

    glVertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x,               y - height / 2,     z                   );

    glVertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius,      y - height / 2,     z                   );
    glVertex3f(x,               y - height / 2,     z                   );

    glVertex3f(x + radius,      y - height / 2,     z                   );
    glVertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x,               y - height / 2,     z                   );

    glVertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x,               y - height / 2,     z                   );

    glVertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius,      y - height / 2,     z                   );
    glVertex3f(x,               y - height / 2,     z                   );



    glVertex3f(x - radius,      y - height / 2,     z                   );
    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius,      y + height / 2,     z                   );

    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius,      y - height / 2,     z                   );
    glVertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );

    glVertex3f(x - radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );

    glVertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x - radius/2,    y + height / 2,     z - M_R3_2 * radius );

    glVertex3f(x + radius,      y - height / 2,     z                   );
    glVertex3f(x + radius,      y + height / 2,     z                   );
    glVertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );

    glVertex3f(x + radius/2,    y + height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius/2,    y - height / 2,     z - M_R3_2 * radius );
    glVertex3f(x + radius,      y - height / 2,     z                   );

    glVertex3f(x - radius,      y - height / 2,     z                   );
    glVertex3f(x - radius,      y + height / 2,     z                   );
    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );

    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius,      y - height / 2,     z                   );

    glVertex3f(x - radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );

    glVertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
    glVertex3f(x - radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );

    glVertex3f(x + radius,      y - height / 2,     z                   );
    glVertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius,      y + height / 2,     z                   );

    glVertex3f(x + radius/2,    y + height / 2,     z + M_R3_2 * radius );
    glVertex3f(x + radius,      y - height / 2,     z                   );
    glVertex3f(x + radius/2,    y - height / 2,     z + M_R3_2 * radius );
}
ChunkView::ChunkView(Chunk *chunk)
    : chunk(chunk) {
}

void ChunkView::gl_init() {
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (BlockWrapper bw : *chunk) {
        switch (bw.block.type) {
            case 1:
                glColor3ub(150, 75, 0);
                break;
            case 2:
                glColor3ub(244, 164, 96);
                break;
            case 3:
                glColor3ub(23, 114, 69);
                break;
            case 4:
                glColor3ub(128, 128, 128);
                break;
        }

        if (bw.block.type != 0) {
            draw_hexagonal_prism(M_R3_2*(bw.j+bw.k), bw.y*M_R3_2, bw.i+0.5*(bw.j-bw.k), M_R3_2, 0.5774);
        }
    }
    glEnd();
    glEndList();
}

void ChunkView::display() {
    glCallList(list);
}
