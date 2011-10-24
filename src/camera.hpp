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
    extern void init();
    extern void move(Direction);
    extern void stop(Direction);
    extern void turn(std::pair<double, double>);
    extern void tick();
    extern void look();
    extern void perspective();
    extern void set_window(int, int);
}
