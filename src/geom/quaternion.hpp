#pragma once

#include <iostream>

#include "vector.hpp"

namespace Geom {
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
}
