#pragma once

#include <iostream>

#include "vector.hpp"

namespace Geom {
    template <typename T, int size>
    struct Point {
        T values[size];

        Point();
        Point(const Point<T, size> &);

        bool operator== (const Point<T, size> &) const;
        bool operator!= (const Point<T, size> &) const;

    };

    template <typename T, int size>
    std::ostream& operator<< (std::ostream &, const Point<T, size> &);

    template <typename T>
    Point<T, 3> operator+ (const Point<T, 3> &, const Vector3 &);

    template <typename T>
    Point<T, 3> operator- (const Point<T, 3> &, const Vector3 &);

    template <typename T>
    Vector3 operator- (const Point<T, 3> &, const Point<T, 3> &);

    extern template struct Point<double, 3>;
    extern template Point<double, 3> operator+ (const Point<double, 3> &, const Vector3 &);
    extern template Point<double, 3> operator- (const Point<double, 3> &, const Vector3 &);
    extern template Vector3 operator- (const Point<double, 3> &, const Point<double, 3> &);
}
