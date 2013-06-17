#pragma once

#include "direction.hpp"
#include "geom.hpp"

class Camera {
    public:
        Camera(int width, int height);

        void gl_init();
        void update_size(int width, int height);

        void move(Direction);
        void stop(Direction);
        void turn(double horizontal, double vertical);
        void tick();
        void look(double interpolation);
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

        Direction moving;
        Direction to_move;
        Direction to_stop;
};
