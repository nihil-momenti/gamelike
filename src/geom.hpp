#ifndef GEOM_HPP
#define GEOM_HPP

#include <iostream>

struct Vector3;

struct Point3 {
    double x, y, z;

    Point3() :
        x(0.0), y(0.0), z(0.0) {
    }

    Point3(double x, double y, double z) :
        x(x), y(y), z(z) {
    }

    Point3(const Point3& other) :
        x(other.x), y(other.y), z(other.z) {
    }

    bool operator== (const Point3& other);
    bool operator!= (const Point3& other);

    Point3 operator+ (const Vector3& other);
    Point3 operator- (const Vector3& other);

    Vector3 operator- (const Point3& other);

    friend std::ostream& operator<< (std::ostream& o, const Point3& point);
};

struct Vector3 {
    double dx, dy, dz;

    Vector3() :
        dx(0.0), dy(0.0), dz(0.0) {
    }

    Vector3(double dx, double dy, double dz) :
        dx(dx), dy(dy), dz(dz) {
    }

    Vector3(const Vector3& other) :
        dx(other.dx), dy(other.dy), dz(other.dz) {
    }

    double length();
    double dot(const Vector3& other);
    Vector3 cross(const Vector3& other);
    Vector3 unit();

    bool operator== (const Vector3& other);
    bool operator!= (const Vector3& other);

    Vector3 operator+ (const Vector3& other);
    Vector3 operator- (const Vector3& other);

    Vector3 operator* (double other);
    Vector3 operator/ (double other);

    friend std::ostream& operator<< (std::ostream& o, const Vector3& vector);
};

inline Vector3 operator- (const Vector3& v) {
    return Vector3(-v.dx, -v.dy, -v.dz);
}

inline Vector3 operator* (double lhs, Vector3 rhs) {
    return rhs * lhs;
}

inline Vector3 operator/ (double lhs, Vector3 rhs) {
    return rhs / lhs;
}

struct Matrix3 {
    double values[9];

    Matrix3();

    // Equivalent to the matlab: m3 = vec1 * vec2'
    Matrix3(const Vector3 &vec1, const Vector3 &vec2);

    static Matrix3 identity();

    Matrix3 transpose();
    Vector3 col(int num);

    Vector3 operator* (const Vector3 &other);
    Matrix3 operator+ (const Matrix3 &other);
    Matrix3 operator- (const Matrix3 &other);
    Matrix3 operator* (double other);
    Matrix3 operator* (const Matrix3 &other);
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

#endif
