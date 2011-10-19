#include "player.hpp"

#define PI 3.1415926535897932384626433832795

#include <SDL.h>
#include "GL_bindings.hpp"

#include <cstdlib>
#include <cmath>

Player::Player() :
    position(0,0,3), lookat(0,0,2), viewup(0,1,0), sensitivity(1.0), speed(2.0)
{
}

void Player::move(Direction direction) {
    moving.insert(direction);
}

void Player::stop(Direction direction) {
    moving.erase(direction);
}

void Player::tick() {
    if (moving.empty()) {
        return;
    }

    Uint32 update_time;
    update_time = SDL_GetTicks();

    for (const Direction &dir : moving) {
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

void Player::look() {
    Vector3 up = side().cross(facing());

    GLdouble M[16] = {
        side().dx,  up.dx,  -facing().dx,   0.0,
        side().dy,  up.dy,  -facing().dy,   0.0,
        side().dz,  up.dz,  -facing().dz,   0.0,
        0.0,        0.0,    0.0,            1.0
    };

    glMultMatrixd(M);
    glTranslated(-position.x, -position.y, -position.z);

    //gluLookAt(
    //    position.x, position.y, position.z,
    //    lookat.x,   lookat.y,   lookat.z,
    //    viewup.dx,  viewup.dy,  viewup.dz
    //);
}

void Player::turn(std::pair<double, double> rotation) {
    Vector3 original_look = lookat - position;

    double x = original_look.dx;
    double y = original_look.dy;
    double z = original_look.dz;

    double r = sqrt(x*x + y*y + z*z);

    double theta = std::max(0.01, std::min(PI - 0.01, acos(y / r) + sensitivity * rotation.second));
    double phi = atan2(z, x) + sensitivity * rotation.first;

    x = r * sin(theta) * cos(phi);
    y = r * cos(theta);
    z = r * sin(theta) * sin(phi);

    lookat = position + Vector3(x, y, z).unit();
}

Vector3 Player::facing() {
    return (lookat - position).unit();
}

Vector3 Player::side() {
    return facing().cross(viewup).unit();
}
void Player::up(double amount) {
    Vector3 movement = amount * viewup;
    position = position + movement;
    lookat = lookat + movement;
}

void Player::forward(double amount) {
    Vector3 movement = amount * facing().unit();
    position = position + movement;
    lookat = lookat + movement;
}

void Player::right(double amount) {
    Vector3 movement = amount * facing().cross(viewup).unit();
    position = position + movement;
    lookat = lookat + movement;
}
