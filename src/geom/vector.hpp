#pragma once

#include <array>
#include <initializer_list>
#include <iostream>

namespace Geom {
    template <typename T, int size>
    struct Vector {
        std::array<T, size> values;

        Vector();
        Vector(const Vector<T, size> &);
        Vector(const std::initializer_list<T> &);

        T length() const;
        T dot(const Vector<T, size> &) const;
        Vector<T, size> cross(const Vector<T, size> &) const;
        Vector<T, size> unit() const;

        bool operator== (const Vector<T, size> &) const;
        bool operator!= (const Vector<T, size> &) const;

        Vector<T, size> & operator+= (const Vector<T, size> &);
        Vector<T, size> & operator-= (const Vector<T, size> &);

        Vector<T, size> & operator*= (T);
        Vector<T, size> & operator/= (T);
    };

    template <typename T, int size>
    Vector<T, size> operator+ (const Vector<T, size> &, const Vector<T, size> &);

    template <typename T, int size>
    Vector<T, size> operator- (const Vector<T, size> &, const Vector<T, size> &);

    template <typename T, int size>
    Vector<T, size> operator* (const Vector<T, size> &, T);

    template <typename T, int size>
    Vector<T, size> operator* (T, const Vector<T, size> &);

    template <typename T, int size>
    Vector<T, size> operator/ (const Vector<T, size> &, T);

    template <typename T, int size>
    Vector<T, size> operator- (const Vector<T, size> &);

    template <typename T, int size>
    std::ostream& operator<< (std::ostream&, const Vector<T, size>&);

    extern template struct Vector<double, 3>;
    extern template Vector<double, 3> operator+ (const Vector<double, 3> &, const Vector<double, 3> &);
    extern template Vector<double, 3> operator- (const Vector<double, 3> &, const Vector<double, 3> &);
    extern template Vector<double, 3> operator* (const Vector<double, 3> &, double);
    extern template Vector<double, 3> operator* (double, const Vector<double, 3> &);
    extern template Vector<double, 3> operator/ (const Vector<double, 3> &, double);
    extern template Vector<double, 3> operator- (const Vector<double, 3> &);
    extern template std::ostream& operator<< (std::ostream&, const Vector<double, 3>&);
}
