#pragma once

#include <iostream>

#include "vector.hpp"

namespace Geom {
    struct Matrix3 {
        double values[9];

        Matrix3();

        // Equivalent to the matlab: m3 = vec1 * vec2'
        Matrix3(const Vector<double, 3> &vec1, const Vector<double, 3> &vec2);

        static Matrix3 identity();

        Matrix3 transpose();
        Vector<double, 3> col(int num);

        Vector<double, 3> operator* (const Vector<double, 3> &rhs);
        Matrix3 operator+ (const Matrix3 &rhs);
        Matrix3 operator- (const Matrix3 &rhs);
        Matrix3 operator* (double rhs);
        Matrix3 operator* (const Matrix3 &rhs);
    };

    inline Matrix3 operator* (double lhs, Matrix3 rhs) {
        return rhs * lhs;
    }

    inline Matrix3 operator/ (Matrix3 lhs, double rhs) {
        return lhs * (1.0 / rhs);
    }

    inline Matrix3 operator/ (double lhs, Matrix3 rhs) {
        return rhs / lhs;
    }
} // namespace Geom
