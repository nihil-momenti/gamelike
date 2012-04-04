#pragma once

#include <iostream>

namespace Geom {
    struct Vector3 {
        double dx, dy, dz;

        Vector3();
        Vector3(const Vector3 &);
        Vector3(double, double, double);

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
}
