static const double M_R3_2 = 0.866025403784439; // sqrt(3) / 2

#include "world_view.hpp"

#include "GL_bindings.hpp"

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
    for (int i = -CHUNK_SIZE; i <= CHUNK_SIZE; i++) {
        for (int j = -CHUNK_SIZE + abs(i); j <= CHUNK_SIZE - abs(i); j++) {
            for (int k = -CHUNK_SIZE + abs(i) + abs(j); k <= CHUNK_SIZE - abs(i) - abs(j); k++) {
                if (world.chunk(i, j, k, 0).type == 1) {
                    glColor3b(10*(i+CHUNK_SIZE), 10*(j+CHUNK_SIZE), 10*(k+CHUNK_SIZE));
                    draw_hexagonal_prism(M_R3_2*(j+k), i+j+k, i+0.5*(j+k), 1, 0.25774);
                }
            }
        }
    }
    glEnd();
}
