#include <cmath>

#include "quaternion.hpp"

namespace Geom {
    Quaternion::Quaternion()
        : Quaternion(0.0, 0.0, 0.0, 0.0) {
    }

    Quaternion::Quaternion(const Quaternion &other)
        : Quaternion(other.r, other.i, other.j, other.k) {
    }

    Quaternion::Quaternion(const Vector<double, 3> &vec)
        : Quaternion(0.0, vec.values[0], vec.values[1], vec.values[2]) {
    }

    Quaternion::Quaternion(double angle, const Vector<double, 3> &vec)
        : Quaternion(
                cos(angle * M_PI_2 / 360),
                vec.values[0] * sin(angle * M_PI_2 / 360),
                vec.values[1] * sin(angle * M_PI_2 / 360),
                vec.values[2] * sin(angle * M_PI_2 / 360)
            ) {
    }

    Quaternion::Quaternion(double r, double i, double j, double k)
        : r(r), i(i), j(j), k(k) {
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
