#include "camera.hpp"

#include "debug.hpp"

#include <SDL.h>
#include "GL_bindings.hpp"

#include <set>

#include <cstdlib>
#include <cmath>

namespace Camera {
    static Point3 position(0, 0, 3);
    static Point3 lookat(0, 0, 2);
    static Vector3 viewup(0, 1, 0);
    static double sensitivity = 0.001;
    static double speed = 0.01;
    static std::set<Direction> moving;
    static Uint32 last_update;
    static double aspect = 0.0;
    static double fov = 50.0;
    static double near = 0.1;
    static double far = 100.0;


    static Vector3 side();
    static Vector3 facing();
    static void up(double);
    static void forward(double);
    static void right(double);

    void init(int width, int height) {
        aspect = width / (double) height;

        glViewport(0, 0, width, height);
    }

    void move(Direction direction) {
        if (moving.empty()) {
            last_update = SDL_GetTicks();
        }
        moving.insert(direction);
    }

    void stop(Direction direction) {
        moving.erase(direction);
    }

    void tick() {
        if (moving.empty()) {
            return;
        }

        Uint32 update_time;
        update_time = SDL_GetTicks();

#if __cplusplus > 199711L
        for (const Direction &dir : moving) {
#else
        for (std::set<Direction>::const_iterator it = moving.begin(); it != moving.end(); it++) {
            const Direction &dir = *it;
#endif
            switch (dir) {
                case FORWARD:  forward( speed * (update_time - last_update)); break;
                case BACK:     forward(-speed * (update_time - last_update)); break;
                case RIGHT:    right(   speed * (update_time - last_update)); break;
                case LEFT:     right(  -speed * (update_time - last_update)); break;
                case UP:       up(      speed * (update_time - last_update)); break;
                case DOWN:     up(     -speed * (update_time - last_update)); break;
            }
        }

        last_update = update_time;
    }

    void look() {
        Vector3 up = side().cross(facing());

        GLdouble M[16] = {
            side().dx,     side().dy,     side().dz,     0.0,
            up.dx,         up.dy,         up.dz,         0.0,
            -facing().dx,  -facing().dy,  -facing().dz,  0.0,
            0.0,           0.0,           0.0,           1.0
        };

        glMultMatrixd(M);
        glTranslated(-position.x, -position.y, -position.z);

        //gluLookAt(
        //    position.x, position.y, position.z,
        //    lookat.x,   lookat.y,   lookat.z,
        //    viewup.dx,  viewup.dy,  viewup.dz
        //);
    }

    void perspective() {
        double f = tan(M_PI_2 - fov * M_PI / 180 / 2);

        GLdouble M[16] = {
            f / aspect, 0.0,    0.0,                                 0.0,
            0.0,        f,      0.0,                                 0.0,
            0.0,        0.0,    (far + near) / (near - far),        -1.0,
            0.0,        0.0,    (2 * far * near) / (near - far),     0.0
        };

        glMultMatrixd(M);
    }

    void turn(std::pair<double, double> rotation) {
        Vector3 original_look = lookat - position;

        double x = original_look.dx;
        double y = original_look.dy;
        double z = original_look.dz;

        double r = sqrt(x*x + y*y + z*z);

        double theta = std::max(0.01, std::min(M_PI - 0.01, acos(y / r) - sensitivity * rotation.second));
        double phi = atan2(z, x) - sensitivity * rotation.first;

        x = r * sin(theta) * cos(phi);
        y = r * cos(theta);
        z = r * sin(theta) * sin(phi);

        lookat = position + Vector3(x, y, z).unit();
    }

    Vector3 facing() {
        return (lookat - position).unit();
    }

    Vector3 side() {
        return facing().cross(viewup).unit();
    }
    void up(double amount) {
        Vector3 movement = amount * viewup;
        position = position + movement;
        lookat = lookat + movement;
    }

    void forward(double amount) {
        Vector3 movement = amount * facing().unit();
        position = position + movement;
        lookat = lookat + movement;
    }

    void right(double amount) {
        Vector3 movement = amount * facing().cross(viewup).unit();
        position = position + movement;
        lookat = lookat + movement;
    }
}
