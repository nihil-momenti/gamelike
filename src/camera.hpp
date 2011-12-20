#pragma once

#include "geom.hpp"

typedef enum {
    FORWARD,
    BACK,
    RIGHT,
    LEFT,
    UP,
    DOWN
} Direction;

namespace Camera {
    void init(int, int);
    void move(Direction);
    void stop(Direction);
    void turn(double, double);
    void tick();
    void look(double);
    void perspective();
}
