#pragma once

#include <iostream>

#include "vector.hpp"

namespace Geom {
    struct Point3 {
        double x, y, z;

        Point3();
        Point3(double, double, double);
        Point3(const Point3 &);

        bool operator== (const Point3 &) const;
        bool operator!= (const Point3 &) const;

        friend Point3 operator+ (const Point3 &, const Vector3 &);
        friend Point3 operator- (const Point3 &, const Vector3 &);

        friend Vector3 operator- (const Point3 &, const Point3 &);

        friend std::ostream& operator<< (std::ostream &, const Point3 &);
    };
}
