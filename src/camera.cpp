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
    static int to_move;
    static int to_stop;

    static SDL_mutex *move_mutex;
    static SDL_mutex *pos_mutex;

    void init(int width, int height) {
        aspect = width / (double) height;

        glViewport(0, 0, width, height);

        move_mutex = SDL_CreateMutex();
        pos_mutex = SDL_CreateMutex();
    }

    Vector3 forward() {
        Vector3 facing = (lookat - position).unit();
        return Vector3(facing.dx, 0, facing.dz).unit();
    }

    Vector3 right() {
        return forward().cross(viewup).unit();
    }

    Vector3 forward(double amount) {
        return amount * forward();
    }

    Vector3 right(double amount) {
        return amount * right();
    }

    Vector3 up(double amount) {
        return amount * viewup;
    }

    Vector3 movement(double interpolation) {
        Vector3 current_movement;

        SDL_LockMutex(move_mutex);
        if (moving & FORWARD) { current_movement += forward(speed * interpolation);  }
        if (moving & BACK)    { current_movement += forward(-speed * interpolation); }
        if (moving & RIGHT)   { current_movement += right(speed * interpolation);    }
        if (moving & LEFT)    { current_movement += right(-speed * interpolation);   }
        if (moving & UP)      { current_movement += up(speed * interpolation);       }
        if (moving & DOWN)    { current_movement += up(-speed * interpolation);      }
        SDL_UnlockMutex(move_mutex);

        return current_movement;
    }

    void move(Direction direction) {
        SDL_LockMutex(move_mutex);
        to_move |= direction;
        SDL_UnlockMutex(move_mutex);
    }

    void stop(Direction direction) {
        SDL_LockMutex(move_mutex);
        to_stop |= direction;
        SDL_UnlockMutex(move_mutex);
    }

    void look(double interpolation) {
        SDL_LockMutex(pos_mutex);
            Vector3 facing = (lookat - position).unit(),
                    side   = facing.cross(viewup).unit(),
                    up     = side.cross(facing).unit();
            Point3 current_position = position + movement(interpolation);
        SDL_UnlockMutex(pos_mutex);

        GLdouble M[16] = {
            side.dx, up.dx, -facing.dx, 0.0,
            side.dy, up.dy, -facing.dy, 0.0,
            side.dz, up.dz, -facing.dz, 0.0,
            0.0,     0.0,   0.0,        1.0
        };

        glMultMatrixd(M);
        glTranslated(-current_position.x, -current_position.y, -current_position.z);
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
        SDL_LockMutex(pos_mutex);
        Vector3 original_look = (lookat - position).unit();
        SDL_UnlockMutex(pos_mutex);

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

        SDL_LockMutex(pos_mutex);
        lookat = position + Vector3(x, y, z).unit();
        SDL_UnlockMutex(pos_mutex);
    }

    void tick() {
        Vector3 current_movement = movement(1.0);

        SDL_LockMutex(pos_mutex);
        position = position + current_movement;
        lookat = lookat + current_movement;
        SDL_UnlockMutex(pos_mutex);

        SDL_LockMutex(move_mutex);
        moving = (moving | to_move) & ~to_stop;
        to_move = to_stop = 0;
        SDL_UnlockMutex(move_mutex);
    }
}
