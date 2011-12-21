#include "camera.hpp"

#include <SDL.h>
#include "GL_bindings.hpp"

#include <cmath>

namespace Camera {
    static Point3 position(0, 0, 3),
                    lookat(0, 0, 2);
    static Vector3  viewup(0, 1, 0);

    static double  sensitivity =   0.001,
                   speed       =   1.0,
                   aspect      =   0.0,
                   fov         =  50.0,
                   near        =   0.1,
                   far         = 100.0;

    // TODO: Find out how to make this Direction, do I need to overload |= or
    // something?
    static int moving;

    void init(int width, int height) {
        aspect = width / (double) height;

        glViewport(0, 0, width, height);
    }

    void move(Direction direction) {
        moving |= direction;
    }

    void stop(Direction direction) {
        moving &= ~direction;
    }

    void look(double interpolation) {
        Vector3 facing = (lookat - position).unit(),
                side   = facing.cross(viewup).unit(),
                up     = side.cross(facing).unit();

        GLdouble M[16] = {
            side.dx, up.dx, -facing.dx, 0.0,
            side.dy, up.dy, -facing.dy, 0.0,
            side.dz, up.dz, -facing.dz, 0.0,
            0.0,     0.0,   0.0,        1.0
        };

        glMultMatrixd(M);
        glTranslated(-position.x, -position.y, -position.z);
    }

    void perspective() {
        double f = tan(M_PI_2 - fov * (M_PI / 180) / 2);

        GLdouble M[16] = {
            f / aspect, 0.0,    0.0,                                 0.0,
            0.0,        f,      0.0,                                 0.0,
            0.0,        0.0,    (far + near) / (near - far),        -1.0,
            0.0,        0.0,    (2 * far * near) / (near - far),     0.0
        };

        glMultMatrixd(M);
    }

    void turn(double horizontal, double vertical) {
        Vector3 original_look = (lookat - position).unit();

        double x = original_look.dx;
        double y = original_look.dy;
        double z = original_look.dz;

        double r = sqrt(x*x + y*y + z*z);

        double theta = acos(y / r) + sensitivity * vertical;
        double phi = atan2(z, x) + sensitivity * horizontal;

        theta = std::max(0.01, theta);
        theta = std::min(M_PI - 0.01, theta);

        x = r * sin(theta) * cos(phi);
        y = r * cos(theta);
        z = r * sin(theta) * sin(phi);

        lookat = position + Vector3(x, y, z).unit();
    }

    Vector3 forward() {
        Vector3 facing = (lookat - position).unit();
        return Vector3(facing.dx, 0, facing.dz).unit();
    }

    Vector3 right() {
        return forward().cross(viewup).unit();
    }

    void forward(double amount) {
        Vector3 movement = amount * forward();
        position = position + movement;
        lookat = lookat + movement;
    }

    void right(double amount) {
        Vector3 movement = amount * right();
        position = position + movement;
        lookat = lookat + movement;
    }

    void up(double amount) {
        Vector3 movement = amount * viewup;
        position = position + movement;
        lookat = lookat + movement;
    }

    void tick() {
        if (moving & FORWARD) { forward(speed);  }
        if (moving & BACK)    { forward(-speed); }
        if (moving & RIGHT)   { right(speed);    }
        if (moving & LEFT)    { right(-speed);   }
        if (moving & UP)      { up(speed);       }
        if (moving & DOWN)    { up(-speed);      }
    }
}
