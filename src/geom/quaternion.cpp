#include <cmath>

#include "quaternion.hpp"

namespace Geom {
    Quaternion::Quaternion()
        : r(0.0), i(0.0), j(0.0), k(0.0) {
    }

    Quaternion::Quaternion(double r, double i, double j, double k)
        : r(r), i(i), j(j), k(k) {
    }

    Quaternion::Quaternion(const Quaternion &other)
        : r(other.r), i(other.i), j(other.j), k(other.k) {
    }

    Quaternion::Quaternion(const Vector3 &vec)
        : r(0.0), i(vec.dx), j(vec.dy), k(vec.dz) {
    }

    Quaternion::Quaternion(double angle, const Vector3 &vec)
        : r(cos(angle * M_PI_2 / 360)), i(vec.dx * sin(angle * M_PI_2 / 360)), j(vec.dy * sin(angle * M_PI_2 / 360)), k(vec.dz * sin(angle * M_PI_2 / 360)) {
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
}
