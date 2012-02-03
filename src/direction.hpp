#pragma once

enum Direction {
    STILL   =  0,
    FORWARD =  1,
    BACK    =  2,
    RIGHT   =  4,
    LEFT    =  8,
    UP      = 16,
    DOWN    = 32,
};

inline Direction operator| (Direction lhs, Direction rhs) {
    return (Direction) ((int)lhs | (int)rhs);
}

inline Direction& operator|= (Direction& lhs, Direction rhs) {
    lhs = lhs | rhs;
    return lhs;
}

inline Direction operator& (Direction lhs, Direction rhs) {
    return (Direction) ((int)lhs & (int)rhs);
}

inline Direction& operator&= (Direction& lhs, Direction rhs) {
    lhs = lhs & rhs;
    return lhs;
}

inline Direction operator~ (Direction& dir) {
    return (Direction) (~(int)dir);
}
