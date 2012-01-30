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

class Camera {
    public:
        Camera(int, int);

        void gl_init();

        void move(Direction);
        void stop(Direction);
        void turn(double, double);
        void tick();
        void look(double);
        void perspective();

    private:
        Geom::Vector3 forward();
        Geom::Vector3 right();
        Geom::Vector3 forward(double);
        Geom::Vector3 right(double);
        Geom::Vector3 up(double);
        Geom::Vector3 movement(double);

        Geom::Point3 position,
                     lookat;
        Geom::Vector3 viewup;

        double sensitivity,
               speed,
               aspect,
               fov,
               near,
               far;

        int width, height;

        // TODO: Find out how to make this Direction, do I need to overload |= or
        // something?
        int moving;
        int to_move;
        int to_stop;
};
