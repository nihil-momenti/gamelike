#pragma once

#include "geom.hpp"

#include <SDL.h>

#include <set>

typedef enum {
    FORWARD,
    BACK,
    RIGHT,
    LEFT,
    UP,
    DOWN
} Direction;

struct Player {
    Point3 position;
    Point3 lookat;
    Vector3 viewup;
    double sensitivity;
    double speed;
    std::set<Direction> moving;
    Uint32 last_update;

    Player();

    void move(Direction);
    void stop(Direction);
    void turn(std::pair<double, double>);
    void tick();
    void look();

    Vector3 side();
    Vector3 facing();
    void up(double);
    void forward(double);
    void right(double);
};
