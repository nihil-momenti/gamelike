#pragma once

#include "direction.hpp"
#include "geom.hpp"

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
        Geom::Vector<double, 3> forward();
        Geom::Vector<double, 3> right();
        Geom::Vector<double, 3> forward(double);
        Geom::Vector<double, 3> right(double);
        Geom::Vector<double, 3> up(double);
        Geom::Vector<double, 3> movement(double);

        Geom::Point<double, 3> position,
                               lookat;
        Geom::Vector<double, 3> viewup;

        double sensitivity,
               speed,
               aspect,
               fov,
               near,
               far;

        int width, height;

        Direction moving;
        Direction to_move;
        Direction to_stop;
};
