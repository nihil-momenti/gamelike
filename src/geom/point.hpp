#pragma once

#include <array>
#include <initializer_list>
#include <iostream>

#include "vector.hpp"

namespace Geom {
    template <typename T, int size>
    struct Point {
        std::array<T, size> values;

        Point();
        Point(const Point<T, size> &);
        Point(const std::initializer_list<T> &);

        bool operator== (const Point<T, size> &) const;
        bool operator!= (const Point<T, size> &) const;

    };

    template <typename T, int size>
    std::ostream& operator<< (std::ostream &, const Point<T, size> &);

    template <typename T, int size>
    Point<T, size> operator+ (const Point<T, size> &, const Vector<T, size> &);

    template <typename T, int size>
    Point<T, size> operator- (const Point<T, size> &, const Vector<T, size> &);

    template <typename T, int size>
    Vector<T, size> operator- (const Point<T, size> &, const Point<T, size> &);

    extern template struct Point<double, 3>;
    extern template std::ostream& operator<< (std::ostream &, const Point<double, 3> &);
    extern template Point<double, 3> operator+ (const Point<double, 3> &, const Vector<double, 3> &);
    extern template Point<double, 3> operator- (const Point<double, 3> &, const Vector<double, 3> &);
    extern template Vector<double, 3> operator- (const Point<double, 3> &, const Point<double, 3> &);
}
