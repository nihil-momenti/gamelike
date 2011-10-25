#include <cmath>

#include "geom.hpp"

//struct Point3 {
    Point3::Point3()
        : x(0.0), y(0.0), z(0.0) {
    }

    Point3::Point3(double x, double y, double z)
        : x(x), y(y), z(z) {
    }

    Point3::Point3(const Point3 &other)
        : x(other.x), y(other.y), z(other.z) {
    }

    bool Point3::operator== (const Point3 &rhs) const {
        return ( (x == rhs.x) && (y == rhs.y) && (z == rhs.z) );
    }

    bool Point3::operator!= (const Point3 &rhs) const {
        return ! (*this == rhs);
    }

    Point3 operator+ (const Point3 &lhs, const Vector3 &rhs) {
        return Point3(lhs.x + rhs.dx, lhs.y + rhs.dy, lhs.z + rhs.dz);
    }

    Point3 operator- (const Point3 &lhs, const Vector3 &rhs) {
        return Point3(lhs.x - rhs.dx, lhs.y - rhs.dy, lhs.z - rhs.dz);
    }

    Vector3 operator- (const Point3 &lhs, const Point3 &rhs) {
        return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    std::ostream& operator<< (std::ostream& o, const Point3& point) {
        return o << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    }
//};


//struct Vector3 {
    Vector3::Vector3() :
        dx(0.0), dy(0.0), dz(0.0) {
    }

    Vector3::Vector3(double dx, double dy, double dz) :
        dx(dx), dy(dy), dz(dz) {
    }

    Vector3::Vector3(const Vector3& other) :
        dx(other.dx), dy(other.dy), dz(other.dz) {
    }

    double Vector3::length() const {
        return sqrt(this->dot(*this));
    }

    double Vector3::dot(const Vector3& other) const {
        return (dx * other.dx) + (dy * other.dy) + (dz * other.dz);
    }

    Vector3 Vector3::cross(const Vector3& other) const {
        return Vector3(
            dy * other.dz - dz * other.dy,
            dz * other.dx - dx * other.dz,
            dx * other.dy - dy * other.dx
        );
    }

    Vector3 Vector3::unit() const {
        return *this / this->length();
    }

    bool Vector3::operator== (const Vector3& rhs) const {
        return ( (dx == rhs.dx) && (dy == rhs.dy) && (dz == rhs.dz) );
    }

    bool Vector3::operator!= (const Vector3& rhs) const {
        return ! (*this == rhs);
    }

    Vector3 & Vector3::operator+= (const Vector3 &rhs) {
        dx += rhs.dx; dy += rhs.dy; dz += rhs.dz;
        return *this;
    }

    Vector3 & Vector3::operator-= (const Vector3 &rhs) {
        return (*this += (-rhs));
    }

    Vector3 & Vector3::operator*= (double rhs) {
        dx *= rhs; dy *= rhs; dz *= rhs;
        return *this;
    }

    Vector3 & Vector3::operator/= (double rhs) {
        return (*this *= (1.0 / rhs));
    }

    Vector3 operator+ (const Vector3 &lhs, const Vector3& rhs) {
        return Vector3(lhs) += rhs;
    }

    Vector3 operator- (const Vector3 &lhs, const Vector3& rhs) {
        return Vector3(lhs) -= rhs;
    }

    Vector3 operator- (const Vector3 &vec) {
        return Vector3(-vec.dx, -vec.dy, -vec.dz);
    }

    Vector3 operator* (const Vector3 &lhs, double rhs) {
        return Vector3(lhs) *= rhs;
    }

    Vector3 operator* (double lhs, const Vector3 &rhs) {
        return Vector3(rhs) *= lhs;
    }

    Vector3 operator/ (const Vector3 &lhs, double rhs) {
        return Vector3(lhs) /= rhs;
    }

    Vector3 operator/ (double lhs, const Vector3 &rhs) {
        return Vector3(rhs) /= lhs;
    }

    std::ostream& operator<< (std::ostream& o, const Vector3& vector) {
        return o << "Vector3(" << vector.dx << ", " << vector.dy << ", " << vector.dz << ")";
    }
//};

//struct Quaternion {
    Quaternion::Quaternion()
        : r(0.0), i(0.0), j(0.0), k(0.0) {
    }

    Quaternion::Quaternion(double r, double i, double j, double k)
        : r(r), i(i), j(j), k(k) {
    }

    Quaternion::Quaternion(const Quaternion& other)
        : r(other.r), i(other.i), j(other.j), k(other.k) {
    }

    double Quaternion::norm() const {
        return sqrt(r*r + i*i + j*j + k*k);
    }

    Quaternion Quaternion::unit() const {
        return Quaternion(*this) / norm();
    }

    bool Quaternion::operator== (const Quaternion &other) const {
        return ((r == other.r) && (i == other.i) && (j == other.j) && (k == other.k));
    }

    bool Quaternion::operator!= (const Quaternion &other) const {
        return ((*this) != other);
    }

    Quaternion & Quaternion::operator+= (const Quaternion &rhs) {
        r += rhs.r;
        i += rhs.i;
        j += rhs.j;
        k += rhs.k;
        return *this;
    }

    Quaternion & Quaternion::operator-= (const Quaternion &rhs) {
        (*this) += (-rhs);
        return *this;
    }

    Quaternion & Quaternion::operator*= (double rhs) {
        r *= rhs;
        i *= rhs;
        j *= rhs;
        k *= rhs;
        return *this;
    }

    Quaternion & Quaternion::operator*= (const Quaternion &rhs) {
        r = r * rhs.r - i * rhs.i - j * rhs.j - k * rhs.k;
        i = r * rhs.i + i * rhs.r + j * rhs.k - k * rhs.j;
        j = r * rhs.j - i * rhs.k + j * rhs.r + k * rhs.i;
        k = r * rhs.k + i * rhs.j - j * rhs.i + k * rhs.r;
        return *this;
    }

    Quaternion & Quaternion::operator/= (double rhs) {
        r /= rhs;
        i /= rhs;
        j /= rhs;
        k /= rhs;
        return *this;
    }

    Quaternion operator+ (const Quaternion &lhs, const Quaternion &rhs) {
        return Quaternion(lhs) += rhs;
    }

    Quaternion operator- (const Quaternion &lhs, const Quaternion &rhs) {
        return Quaternion(lhs) -= rhs;
    }

    Quaternion operator* (const Quaternion &lhs, const Quaternion &rhs) {
        return Quaternion(lhs) *= rhs;
    }

    Quaternion operator* (const Quaternion &lhs, double rhs) {
        return Quaternion(lhs) *= rhs;
    }

    Quaternion operator* (double lhs, const Quaternion &rhs) {
        return Quaternion(rhs) *= lhs;
    }

    Quaternion operator/ (const Quaternion &lhs, double rhs) {
        return Quaternion(lhs) /= rhs;
    }

    Quaternion operator- (const Quaternion &q) {
        return Quaternion(-q.r, -q.i, -q.j, -q.k);
    }

    std::ostream& operator<< (std::ostream &o, const Quaternion &q) {
        return o << "Quaternion(" << q.r << ", " << q.i << ", " << q.j << ", " << q.k << ")";
    }
//}

//struct Matrix3 {
    Matrix3::Matrix3() {
        values[0] = values[1] = values[2] = 0.0;
        values[3] = values[4] = values[5] = 0.0;
        values[6] = values[7] = values[8] = 0.0;
    }

    Matrix3::Matrix3(const Vector3 &vec1, const Vector3 &vec2) {
        values[0] = vec1.dx * vec2.dx;
        values[1] = vec1.dx * vec2.dy;
        values[2] = vec1.dx * vec2.dz;
        values[3] = vec1.dy * vec2.dx;
        values[4] = vec1.dy * vec2.dy;
        values[5] = vec1.dy * vec2.dz;
        values[6] = vec1.dz * vec2.dx;
        values[7] = vec1.dz * vec2.dy;
        values[8] = vec1.dz * vec2.dz;
    }

    Matrix3 Matrix3::identity() {
        Matrix3 I = Matrix3();
        I.values[0] = I.values[4] = I.values[8] = 1.0;
        return I;
    }

    Vector3 Matrix3::operator*(const Vector3 &rhs) {
        double dx = values[0] * rhs.dx + values[1] * rhs.dy + values[2] * rhs.dz;
        double dy = values[3] * rhs.dx + values[4] * rhs.dy + values[5] * rhs.dz;
        double dz = values[6] * rhs.dx + values[7] * rhs.dy + values[8] * rhs.dz;
        return Vector3(dx, dy, dz);
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

    Vector3 Matrix3::col(int num) {
        switch (num) {
            case 0:
                return Vector3(values[0], values[3], values[6]);
            case 1:
                return Vector3(values[1], values[4], values[7]);
            case 2:
                return Vector3(values[2], values[5], values[8]);
            default:
                return Vector3();
        }
    }
//};
