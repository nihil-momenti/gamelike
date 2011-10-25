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
    extern void init(int, int);
    extern void move(Direction);
    extern void stop(Direction);
    extern void turn(double, double);
    extern void tick();
    extern void look(double);
    extern void perspective();
}
