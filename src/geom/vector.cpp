#include <cmath>

#include "vector.hpp"

namespace Geom {
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
}
