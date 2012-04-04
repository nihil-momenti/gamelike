#include <cmath>

#include "matrix.hpp"

namespace Geom {
    Matrix3::Matrix3() {
        values[0] = values[1] = values[2] = 0.0;
        values[3] = values[4] = values[5] = 0.0;
        values[6] = values[7] = values[8] = 0.0;
    }

    Matrix3::Matrix3(const Vector<double, 3> &vec1, const Vector<double, 3> &vec2) {
        values[0] = vec1.values[0] * vec2.values[0];
        values[1] = vec1.values[0] * vec2.values[1];
        values[2] = vec1.values[0] * vec2.values[2];
        values[3] = vec1.values[1] * vec2.values[0];
        values[4] = vec1.values[1] * vec2.values[1];
        values[5] = vec1.values[1] * vec2.values[2];
        values[6] = vec1.values[2] * vec2.values[0];
        values[7] = vec1.values[2] * vec2.values[1];
        values[8] = vec1.values[2] * vec2.values[2];
    }

    Matrix3 Matrix3::identity() {
        Matrix3 I = Matrix3();
        I.values[0] = I.values[4] = I.values[8] = 1.0;
        return I;
    }

    Vector<double, 3> Matrix3::operator*(const Vector<double, 3> &rhs) {
        Vector<double, 3> result;
        result.values[0] = values[0] * rhs.values[0] + values[1] * rhs.values[1] + values[2] * rhs.values[2];
        result.values[1] = values[3] * rhs.values[0] + values[4] * rhs.values[1] + values[5] * rhs.values[2];
        result.values[2] = values[6] * rhs.values[0] + values[7] * rhs.values[1] + values[8] * rhs.values[2];
        return result;
    }

    Matrix3 Matrix3::operator+(const Matrix3 &rhs) {
        Matrix3 m = Matrix3();
        for (int i = 0; i < 9; i++) {
            m.values[i] = values[i] - rhs.values[i];
        }
        return m;
    }

    Matrix3 Matrix3::operator-(const Matrix3 &rhs) {
        Matrix3 m = Matrix3();
        for (int i = 0; i < 9; i++) {
            m.values[i] = values[i] - rhs.values[i];
        }
        return m;
    }

    Matrix3 Matrix3::operator* (double rhs) {
        Matrix3 m = Matrix3();
        for (int i = 0; i < 9; i++) {
            m.values[i] = values[i] * rhs;
        }
        return m;
    }

    Matrix3 Matrix3::operator* (const Matrix3 &rhs) {
        Matrix3 m = Matrix3();

        m.values[0] = values[0] * rhs.values[0]
                    + values[1] * rhs.values[3]
                    + values[2] * rhs.values[6];

        m.values[1] = values[0] * rhs.values[1]
                    + values[1] * rhs.values[4]
                    + values[2] * rhs.values[7];

        m.values[2] = values[0] * rhs.values[2]
                    + values[1] * rhs.values[5]
                    + values[2] * rhs.values[8];

        m.values[3] = values[3] * rhs.values[0]
                    + values[4] * rhs.values[3]
                    + values[5] * rhs.values[6];

        m.values[4] = values[3] * rhs.values[1]
                    + values[4] * rhs.values[4]
                    + values[5] * rhs.values[7];

        m.values[5] = values[3] * rhs.values[2]
                    + values[4] * rhs.values[5]
                    + values[5] * rhs.values[8];

        m.values[6] = values[6] * rhs.values[0]
                    + values[7] * rhs.values[3]
                    + values[8] * rhs.values[6];

        m.values[7] = values[6] * rhs.values[1]
                    + values[7] * rhs.values[4]
                    + values[8] * rhs.values[7];

        m.values[8] = values[6] * rhs.values[2]
                    + values[7] * rhs.values[5]
                    + values[8] * rhs.values[8];

        return m;
    }

    Matrix3 Matrix3::transpose() {
        Matrix3 m = Matrix3();

        m.values[0] = values[0];
        m.values[1] = values[3];
        m.values[2] = values[6];
        m.values[3] = values[1];
        m.values[4] = values[4];
        m.values[5] = values[7];
        m.values[6] = values[2];
        m.values[7] = values[5];
        m.values[8] = values[8];

        return m;
    }

    Vector<double, 3> Matrix3::col(int num) {
        Vector<double, 3> result;
        switch (num) {
            case 0:
                result.values[0] = values[0];
                result.values[1] = values[3];
                result.values[2] = values[6];
                break;
            case 1:
                result.values[0] = values[1];
                result.values[1] = values[4];
                result.values[2] = values[7];
                break;
            case 2:
                result.values[0] = values[2];
                result.values[1] = values[5];
                result.values[2] = values[8];
                break;
            default:
                break;
        }
        return result;
    }
}
