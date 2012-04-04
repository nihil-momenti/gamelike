#include <cmath>

#include "vector.hpp"

namespace Geom {
    template <typename T, int size>
    Vector<T, size>::Vector()
        : values() {
    }

    template <typename T, int size>
    Vector<T, size>::Vector(const Vector<T, size>& other)
        : values(other.values) {
    }

    template <typename T, int size>
    Vector<T, size>::Vector(const std::initializer_list<T> &init_list)
        : values(init_list) {
    }

    template <typename T, int size>
    T Vector<T, size>::length() const {
        return sqrt(this->dot(*this));
    }

    template <typename T, int size>
    T Vector<T, size>::dot(const Vector<T, size>& other) const {
        T result = T();
        for (int i = 0; i < size; i++) {
            result += values[i] * other.values[i];
        }
        return result;
    }

    template <typename T, int size>
    Vector<T, size> Vector<T, size>::cross(const Vector<T, size>& other) const {
        Vector<T, size> vector;
        vector.values[0] = values[1] * other.values[2] - values[2] * other.values[1];
        vector.values[1] = values[2] * other.values[0] - values[0] * other.values[2];
        vector.values[2] = values[0] * other.values[1] - values[1] * other.values[0];
        return vector;
    }

    template <typename T, int size>
    Vector<T, size> Vector<T, size>::unit() const {
        return *this / this->length();
    }

    template <typename T, int size>
    bool Vector<T, size>::operator== (const Vector<T, size>& rhs) const {
        for (int i = 0; i < size; i++) {
            if (values[i] != rhs.values[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T, int size>
    bool Vector<T, size>::operator!= (const Vector<T, size>& rhs) const {
        return ! (*this == rhs);
    }

    template <typename T, int size>
    Vector<T, size> & Vector<T, size>::operator+= (const Vector<T, size> &rhs) {
        for (int i = 0; i < size; i++) {
            values[i] += rhs.values[i];
        }
        return *this;
    }

    template <typename T, int size>
    Vector<T, size> & Vector<T, size>::operator-= (const Vector<T, size> &rhs) {
        return (*this += (-rhs));
    }

    template <typename T, int size>
    Vector<T, size> & Vector<T, size>::operator*= (T rhs) {
        for (int i = 0; i < size; i++) {
            values[i] *= rhs;
        }
        return *this;
    }

    template <typename T, int size>
    Vector<T, size> & Vector<T, size>::operator/= (T rhs) {
        return (*this *= (static_cast<T>(1) / rhs));
    }

    template <typename T, int size>
    Vector<T, size> operator+ (const Vector<T, size> &lhs, const Vector<T, size> &rhs) {
         Vector<T, size> result(lhs);
         result += rhs;
         return result;
    }

    template <typename T, int size>
    Vector<T, size> operator- (const Vector<T, size> &lhs, const Vector<T, size> &rhs) {
        return Vector<T, size>(lhs) -= rhs;
    }

    template <typename T, int size>
    Vector<T, size> operator- (const Vector<T, size> &vec) {
        return Vector<T, size>() -= vec;
    }

    template <typename T, int size>
    Vector<T, size> operator* (const Vector<T, size> &lhs, T rhs) {
        return Vector<T, size>(lhs) *= rhs;
    }

    template <typename T, int size>
    Vector<T, size> operator* (T lhs, const Vector<T, size> &rhs) {
        return Vector<T, size>(rhs) *= lhs;
    }

    template <typename T, int size>
    Vector<T, size> operator/ (const Vector<T, size> &lhs, T rhs) {
        return Vector<T, size>(lhs) /= rhs;
    }

    template <typename T, int size>
    Vector<T, size> operator/ (T lhs, const Vector<T, size> &rhs) {
        return Vector<T, size>(rhs) /= lhs;
    }

    template <typename T, int size>
    std::ostream& operator<< (std::ostream& out_stream, const Vector<T, size>& vector) {
        out_stream << "(" << vector.values[0];
        for (int i = 1; i < size; i++) {
            out_stream << ", " << vector.values[i];
        }
        out_stream << ")";
        return out_stream;
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& out_stream, const Vector<T, 0>& vector) {
        return out_stream << "(" << ")";
    }

    template struct Vector<double, 3>;
    template Vector<double, 3> operator+ (const Vector<double, 3> &, const Vector<double, 3> &);
    template Vector<double, 3> operator- (const Vector<double, 3> &, const Vector<double, 3> &);
    template Vector<double, 3> operator* (const Vector<double, 3> &, double);
    template Vector<double, 3> operator* (double, const Vector<double, 3> &);
    template Vector<double, 3> operator/ (const Vector<double, 3> &, double);
    template Vector<double, 3> operator- (const Vector<double, 3> &);
    template std::ostream& operator<< (std::ostream&, const Vector<double, 3>&);
}
