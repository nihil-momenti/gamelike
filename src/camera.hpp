#pragma once

#include "geom.hpp"

typedef enum {
    FORWARD =  1,
    BACK    =  2,
    RIGHT   =  4,
    LEFT    =  8,
    UP      = 16,
    DOWN    = 32
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
