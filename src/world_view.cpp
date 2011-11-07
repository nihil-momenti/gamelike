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

void draw_block(Block &block, int i, int j, int k, int y) {
    if (block.type == 1) {
        glColor3ub(std::min(5*abs(i)*y, 255), std::min(5*abs(j)*y, 255), std::min(5*abs(k)*y, 255));
        draw_hexagonal_prism(M_R3_2*(j+k), y, i+0.5*(j-k), 1, 0.5774);
    }
}

void WorldView::display() {
    glBegin(GL_TRIANGLES);
    world.chunk.each(draw_block);
    glEnd();
}
