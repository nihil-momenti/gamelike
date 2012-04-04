#include <cmath>

#include "point.hpp"

namespace Geom {
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
}
