#include "camera.hpp"

#include <SDL.h>
#include "GL_bindings.hpp"

#include <cmath>

Camera::Camera(int width, int height)
        : position(0,0,3),
          lookat(0,0,2),
          viewup(0,1,0),
          sensitivity(0.001),
          speed(1.0),
          aspect(width/(double)height),
          fov(50.0),
          near(0.1),
          far(100.0),
          width(width),
          height(height),
          moving(0),
          to_move(0),
          to_stop(0) {
}

void Camera::gl_init() {
    GL::Viewport(0, 0, width, height);
}

Geom::Vector3 Camera::forward() {
    Geom::Vector3 facing = (lookat - position).unit();
    return Geom::Vector3(facing.dx, 0, facing.dz).unit();
}

Geom::Vector3 Camera::right() {
    return forward().cross(viewup).unit();
}

Geom::Vector3 Camera::forward(double amount) {
    return amount * forward();
}

Geom::Vector3 Camera::right(double amount) {
    return amount * right();
}

Geom::Vector3 Camera::up(double amount) {
    return amount * viewup;
}

Geom::Vector3 Camera::movement(double interpolation) {
    Geom::Vector3 current_movement;

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

void Camera::tick() {
    Geom::Vector3 current_movement = movement(1.0);

    position = position + current_movement;
    lookat = lookat + current_movement;

    moving = (moving | to_move) & ~to_stop;
    to_move = to_stop = 0;
}
