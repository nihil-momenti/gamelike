static const double M_R3_2 = 0.866025403784439; // sqrt(3) / 2

#include "world_view.hpp"

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

WorldView::WorldView() {
}

WorldView::WorldView(World world) 
    : world(world)
{
}

void WorldView::gl_init() {}

void WorldView::display() {
    glBegin(GL_TRIANGLES);
    for (BlockWrapper bw : world.chunk) {
        if (bw.block.type == 1) {
            glColor3ub(std::min(5*abs(bw.i)*bw.y, 255), std::min(5*abs(bw.j)*bw.y, 255), std::min(5*abs(bw.k)*bw.y, 255));
            draw_hexagonal_prism(M_R3_2*(bw.j+bw.k), bw.y, bw.i+0.5*(bw.j-bw.k), 1, 0.5774);
        }
    }
    glEnd();
}
