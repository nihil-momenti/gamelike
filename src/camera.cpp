#include "camera.hpp"

#include <SDL.h>
#include "GL_bindings.hpp"

#include <cmath>

Camera::Camera(int width, int height)
        : position({0, 0, 3}),
          lookat({0, 0, 2}),
          viewup({0, 1, 0}),
          sensitivity(0.001),
          speed(1.0),
          aspect(width/(double)height),
          fov(50.0),
          near(0.1),
          far(100.0),
          width(width),
          height(height),
          moving(STILL),
          to_move(STILL),
          to_stop(STILL) {
}

void Camera::gl_init() {
    GL::Viewport(0, 0, width, height);
}

Geom::Vector<double, 3> Camera::forward() {
    Geom::Vector<double, 3> facing = lookat - position;
    facing.values[1] = 0;
    return facing.unit();
}

Geom::Vector<double, 3> Camera::right() {
    return forward().cross(viewup).unit();
}

Geom::Vector<double, 3> Camera::forward(double amount) {
    return amount * forward();
}

Geom::Vector<double, 3> Camera::right(double amount) {
    return amount * right();
}

Geom::Vector<double, 3> Camera::up(double amount) {
    return amount * viewup;
}

Geom::Vector<double, 3> Camera::movement(double interpolation) {
    Geom::Vector<double, 3> current_movement;

    if (moving & FORWARD) { current_movement += forward(speed * interpolation);  }
    if (moving & BACK)    { current_movement += forward(-speed * interpolation); }
    if (moving & RIGHT)   { current_movement += right(speed * interpolation);    }
    if (moving & LEFT)    { current_movement += right(-speed * interpolation);   }
    if (moving & UP)      { current_movement += up(speed * interpolation);       }
    if (moving & DOWN)    { current_movement += up(-speed * interpolation);      }

    return current_movement;
}

void Camera::move(Direction direction) {
    to_move |= direction;
}

void Camera::stop(Direction direction) {
    to_stop |= direction;
}

void Camera::look(double interpolation) {
    Geom::Vector<double, 3> facing = (lookat - position).unit(),
                            side   = facing.cross(viewup).unit(),
                            up     = side.cross(facing).unit();
    Geom::Point<double, 3> current_position = position + movement(interpolation);

    GLdouble M[16] = {
        side.values[0], up.values[0], -facing.values[0], 0.0,
        side.values[1], up.values[1], -facing.values[1], 0.0,
        side.values[2], up.values[2], -facing.values[2], 0.0,
        0.0,     0.0,   0.0,        1.0
    };

    GL::MultMatrixd(M);
    GL::Translated(-current_position.values[0], -current_position.values[1], -current_position.values[2]);
}

void Camera::perspective() {
    double f = tan(M_PI_2 - fov * (M_PI / 180) / 2);

    GLdouble M[16] = {
        f / aspect, 0.0,    0.0,                                 0.0,
        0.0,        f,      0.0,                                 0.0,
        0.0,        0.0,    (far + near) / (near - far),        -1.0,
        0.0,        0.0,    (2 * far * near) / (near - far),     0.0
    };

    GL::MultMatrixd(M);
}

void Camera::turn(double horizontal, double vertical) {
    Geom::Vector<double, 3> original_look = (lookat - position).unit();

    double x = original_look.values[0];
    double y = original_look.values[1];
    double z = original_look.values[2];

    double r = sqrt(x*x + y*y + z*z);

    double theta = acos(y / r) + sensitivity * vertical;
    double phi = atan2(z, x) + sensitivity * horizontal;

    theta = std::max(0.01, theta);
    theta = std::min(M_PI - 0.01, theta);

    x = r * sin(theta) * cos(phi);
    y = r * cos(theta);
    z = r * sin(theta) * sin(phi);


    Geom::Vector<double, 3> new_look;
    new_look.values[0] = x;
    new_look.values[1] = y;
    new_look.values[2] = z;

    lookat = position + new_look.unit();
}

void Camera::tick() {
    Geom::Vector<double, 3> current_movement = movement(1.0);

    position = position + current_movement;
    lookat = lookat + current_movement;

    moving = (moving | to_move) & ~to_stop;
    to_move = to_stop = STILL;
}
