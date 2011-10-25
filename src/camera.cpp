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
    static double speed = 1.0;
    static std::set<Direction> moving;
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
        moving.insert(direction);
    }

    void stop(Direction direction) {
        moving.erase(direction);
    }

    void tick() {
        if (moving.empty()) {
            return;
        }

#if __cplusplus > 199711L
        for (const Direction &dir : moving) {
#else
        for (std::set<Direction>::const_iterator it = moving.begin(); it != moving.end(); it++) {
            const Direction &dir = *it;
#endif
            switch (dir) {
                case FORWARD:  forward(speed);  break;
                case BACK:     forward(-speed); break;
                case RIGHT:    right(speed);    break;
                case LEFT:     right(-speed);   break;
                case UP:       up(speed);       break;
                case DOWN:     up(-speed);      break;
            }
        }
    }

    void look(double interpolation) {
        Vector3 up = side().cross(facing()).unit();

        GLdouble M[16] = {
        //    side().dx,     side().dy,     side().dz,     0.0,
        //    up.dx,         up.dy,         up.dz,         0.0,
        //    -facing().dx,  -facing().dy,  -facing().dz,  0.0,
        //    0.0,           0.0,           0.0,           1.0
            side().dx,      up.dx,      -facing().dx,       0.0,
            side().dy,      up.dy,      -facing().dy,       0.0,
            side().dz,      up.dz,      -facing().dz,       0.0,
            0.0,            0.0,        0.0,                1.0
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

    void turn(double horizontal, double vertical) {
        Vector3 original_look = facing();

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
        Vector3 movement = amount * facing();
        position = position + movement;
        lookat = lookat + movement;
    }

    void right(double amount) {
        Vector3 movement = amount * side();
        position = position + movement;
        lookat = lookat + movement;
    }
}
