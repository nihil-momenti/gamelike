#ifndef GEOM_HPP
#define GEOM_HPP

#include <iostream>

struct Vector3;

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

struct Vector3 {
    double dx, dy, dz;

    Vector3();
    Vector3(double, double, double);
    Vector3(const Vector3 &);

    double length() const;
    double dot(const Vector3 &) const;
    Vector3 cross(const Vector3 &) const;
    Vector3 unit() const;

    bool operator== (const Vector3 &) const;
    bool operator!= (const Vector3 &) const;

    Vector3 & operator+= (const Vector3 &);
    Vector3 & operator-= (const Vector3 &);

    Vector3 & operator*= (double);
    Vector3 & operator/= (double);

    friend Vector3 operator+ (const Vector3 &, const Vector3 &);
    friend Vector3 operator- (const Vector3 &, const Vector3 &);

    friend Vector3 operator* (const Vector3 &, double);
    friend Vector3 operator* (double, const Vector3 &);
    friend Vector3 operator/ (const Vector3 &, double);

    friend Vector3 operator- (const Vector3 &);

    friend std::ostream& operator<< (std::ostream&, const Vector3&);
};

struct Quaternion {
    double r, i, j, k;

    Quaternion();
    Quaternion(double, double, double, double);
    Quaternion(const Quaternion &);
    Quaternion(const Vector3 &);
    Quaternion(double, const Vector3 &);

    double norm() const;
    Quaternion unit() const;

    bool operator== (const Quaternion &) const;
    bool operator!= (const Quaternion &) const;

    Quaternion & operator+= (const Quaternion &);
    Quaternion & operator-= (const Quaternion &);
    Quaternion & operator*= (const Quaternion &);

    Quaternion & operator*= (double);
    Quaternion & operator/= (double);

    friend Quaternion operator+ (const Quaternion &, const Quaternion &);
    friend Quaternion operator- (const Quaternion &, const Quaternion &);

    friend Quaternion operator* (const Quaternion &, double);
    friend Quaternion operator* (double, const Quaternion &);
    friend Quaternion operator/ (const Quaternion &, double);

    friend Quaternion operator- (const Quaternion &);

    friend std::ostream& operator<< (std::ostream &, const Quaternion &);
};

struct Matrix3 {
    double values[9];

    Matrix3();

    // Equivalent to the matlab: m3 = vec1 * vec2'
    Matrix3(const Vector3 &vec1, const Vector3 &vec2);

    static Matrix3 identity();

    Matrix3 transpose();
    Vector3 col(int num);

    Vector3 operator* (const Vector3 &rhs);
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

#endif
