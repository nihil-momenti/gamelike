#include <cmath>

#include "point.hpp"

namespace Geom {
    template <typename T, int size>
    Point<T, size>::Point()
        : values() {
    }

    template <typename T, int size>
    Point<T, size>::Point(const Point<T, size> &other)
        : values(other.values) {
    }

    template <typename T, int size>
    Point<T, size>::Point(const std::initializer_list<T> &init_list)
        : values(init_list) {
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

    template <typename T, int size>
    Point<T, size> operator+ (const Point<T, size> &lhs, const Vector<T, size> &rhs) {
        Point<T, size> point;
        for (int i = 0; i < size; i++) {
            point.values[i] = lhs.values[i] + rhs.values[i];
        }
        return point;
    }

    template <typename T, int size>
    Point<T, size> operator- (const Point<T, size> &lhs, const Vector<T, size> &rhs) {
        Point<T, size> point;
        for (int i = 0; i < size; i++) {
            point.values[i] = lhs.values[i] - rhs.values[i];
        }
        return point;
    }

    template <typename T, int size>
    Vector<T, size> operator- (const Point<T, size> &lhs, const Point<T, size> &rhs) {
        Vector<T, size> vector;
        for (int i = 0; i < size; i++) {
            vector.values[i] = lhs.values[i] - rhs.values[i];
        }
        return vector;
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
    template std::ostream& operator<< (std::ostream &, const Point<double, 3> &);
    template Point<double, 3> operator+ (const Point<double, 3> &, const Vector<double, 3> &);
    template Point<double, 3> operator- (const Point<double, 3> &, const Vector<double, 3> &);
    template Vector<double, 3> operator- (const Point<double, 3> &, const Point<double, 3> &);
}
