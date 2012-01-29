#include "camera.hpp"

#include <SDL.h>
#include "GL_bindings.hpp"

#include "geom.hpp"

#include <cmath>

namespace Camera {
    static Geom::Point3 position(0, 0, 3),
                        lookat(0, 0, 2);
    static Geom::Vector3 viewup(0, 1, 0);

    static double  sensitivity =   0.001,
                   speed       =   1.0,
                   aspect      =   0.0,
                   fov         =  50.0,
                   near        =   0.1,
                   far         = 100.0;

    // TODO: Find out how to make this Direction, do I need to overload |= or
    // something?
    static int moving;
    static int to_move;
    static int to_stop;

    void init(int width, int height) {
        aspect = width / (double) height;

        GL::Viewport(0, 0, width, height);
    }

    Geom::Vector3 forward() {
        Geom::Vector3 facing = (lookat - position).unit();
        return Geom::Vector3(facing.dx, 0, facing.dz).unit();
    }

    Geom::Vector3 right() {
        return forward().cross(viewup).unit();
    }

    Geom::Vector3 forward(double amount) {
        return amount * forward();
    }

    Geom::Vector3 right(double amount) {
        return amount * right();
    }

    Geom::Vector3 up(double amount) {
        return amount * viewup;
    }

    Geom::Vector3 movement(double interpolation) {
        Geom::Vector3 current_movement;

        if (moving & FORWARD) { current_movement += forward(speed * interpolation);  }
        if (moving & BACK)    { current_movement += forward(-speed * interpolation); }
        if (moving & RIGHT)   { current_movement += right(speed * interpolation);    }
        if (moving & LEFT)    { current_movement += right(-speed * interpolation);   }
        if (moving & UP)      { current_movement += up(speed * interpolation);       }
        if (moving & DOWN)    { current_movement += up(-speed * interpolation);      }

        return current_movement;
    }

    void move(Direction direction) {
        to_move |= direction;
    }

    void stop(Direction direction) {
        to_stop |= direction;
    }

    void look(double interpolation) {
        Geom::Vector3 facing = (lookat - position).unit(),
                      side   = facing.cross(viewup).unit(),
                      up     = side.cross(facing).unit();
        Geom::Point3 current_position = position + movement(interpolation);

        GLdouble M[16] = {
            side.dx, up.dx, -facing.dx, 0.0,
            side.dy, up.dy, -facing.dy, 0.0,
            side.dz, up.dz, -facing.dz, 0.0,
            0.0,     0.0,   0.0,        1.0
        };

        GL::MultMatrixd(M);
        GL::Translated(-current_position.x, -current_position.y, -current_position.z);
    }

    void perspective() {
        double f = tan(M_PI_2 - fov * (M_PI / 180) / 2);

        GLdouble M[16] = {
            f / aspect, 0.0,    0.0,                                 0.0,
            0.0,        f,      0.0,                                 0.0,
            0.0,        0.0,    (far + near) / (near - far),        -1.0,
            0.0,        0.0,    (2 * far * near) / (near - far),     0.0
        };

        GL::MultMatrixd(M);
    }

    void turn(double horizontal, double vertical) {
        Geom::Vector3 original_look = (lookat - position).unit();

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

        lookat = position + Geom::Vector3(x, y, z).unit();
    }

    void tick() {
        Geom::Vector3 current_movement = movement(1.0);

        position = position + current_movement;
        lookat = lookat + current_movement;

        moving = (moving | to_move) & ~to_stop;
        to_move = to_stop = 0;
    }
}
