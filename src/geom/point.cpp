#include <cmath>

#include "point.hpp"

namespace Geom {
    template <typename T, int size>
    Point<T, size>::Point() {
        for (T& value : values) {
            value = T();
        }
    }

    template <typename T, int size>
    Point<T, size>::Point(const Point<T, size> &other) {
        for (int i = 0; i < size; i++) {
            values[i] = other.values[i];
        }
    }

    template <typename T, int size>
    bool Point<T, size>::operator== (const Point<T, size> &rhs) const {
        for (int i = 0; i < size; i++) {
            if (values[i] != rhs.values[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T, int size>
    bool Point<T, size>::operator!= (const Point<T, size> &rhs) const {
        return ! (*this == rhs);
    }

    template <typename T>
    Point<T, 3> operator+ (const Point<T, 3> &lhs, const Vector3 &rhs) {
        Point<T, 3> point;

        point.values[0] = lhs.values[0] + rhs.dx;
        point.values[1] = lhs.values[1] + rhs.dy;
        point.values[2] = lhs.values[2] + rhs.dz;

        return point;
    }

    template <typename T>
    Point<T, 3> operator- (const Point<T, 3> &lhs, const Vector3 &rhs) {
        Point<T, 3> point;

        point.values[0] = lhs.values[0] - rhs.dx;
        point.values[1] = lhs.values[1] - rhs.dy;
        point.values[2] = lhs.values[2] - rhs.dz;

        return point;
    }

    template <typename T>
    Vector3 operator- (const Point<T, 3> &lhs, const Point<T, 3> &rhs) {
        return Vector3(
                lhs.values[0] - rhs.values[0],
                lhs.values[1] - rhs.values[1],
                lhs.values[2] - rhs.values[2]
            );
    }

    template <typename T, int size>
    std::ostream& operator<< (std::ostream& out_stream, const Point<T, size>& point) {
        out_stream << "(" << point.values[0];
        for (int i = 1; i < size; i++) {
            out_stream << ", " << point.values[i];
        }
        out_stream << ")";
        return out_stream;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& out_stream, const Point<T, 0>& point) {
        return out_stream << "(" << ")";
    }

    template struct Point<double, 3>;
    template Point<double, 3> operator+ (const Point<double, 3> &, const Vector3 &);
    template Point<double, 3> operator- (const Point<double, 3> &, const Vector3 &);
    template Vector3 operator- (const Point<double, 3> &, const Point<double, 3> &);
}
