#pragma once

#include "Precision.h"
#include <cmath>
#include <iostream>

class Vec3 {
  public:
    // 1. Constructor
    Vec3() : e_{0, 0, 0} {}
    Vec3(real_t e0, real_t e1, real_t e2) : e_{e0, e1, e2} {}

    // 2. Getter/Setter
    real_t x() const { return e_[0]; }
    real_t y() const { return e_[1]; }
    real_t z() const { return e_[2]; }

    // Static utiliies
    static Vec3 Random() { return Vec3(RandomReal(), RandomReal(), RandomReal()); }
    static Vec3 Random(real_t min, real_t max) {
        return Vec3(RandomReal(min, max), RandomReal(min, max), RandomReal(min, max));
    }

    // 3. Member functions
    real_t Length() const { return std::sqrt(LengthSquared()); }
    real_t LengthSquared() const { return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2]; }

    bool NearZero() const {
        real_t s = 1e-8;
        return (std::fabs(e_[0] < s)) && (std::fabs(e_[1] < s)) && (std::fabs(e_[2] < s));
    }

    // 4. Operators
    Vec3 operator-() const { return Vec3(-e_[0], -e_[1], -e_[2]); }
    real_t operator[](int i) const { return e_[i]; }
    real_t &operator[](int i) { return e_[i]; }

    Vec3 &operator+=(const Vec3 &v) {
        e_[0] += v.e_[0];
        e_[1] += v.e_[1];
        e_[2] += v.e_[2];
        return *this;
    }

    Vec3 &operator*=(real_t t) {
        e_[0] *= t;
        e_[1] *= t;
        e_[2] *= t;
        return *this;
    }

    Vec3 &operator/=(real_t t) { return *this *= 1 / t; }

  private:
    // 5. Member variables
    real_t e_[3];
};

using Point3 = Vec3; // 3D point (just an alias)

// Vec3 Utility Functions
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(real_t t, const Vec3 &v) { return Vec3(t * v[0], t * v[1], t * v[2]); }

inline Vec3 operator*(const Vec3 &v, real_t t) { return t * v; }

inline Vec3 operator/(const Vec3 &v, real_t t) { return (1 / t) * v; }

inline real_t Dot(const Vec3 &u, const Vec3 &v) { return u[0] * v[0] + u[1] * v[1] + u[2] * v[2]; }

inline Vec3 Cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]);
}

inline Vec3 Normalize(const Vec3 &v) { return v / v.Length(); }

// Rejection method
inline Vec3 RandomUnitVector() {
    while (true) {
        Point3 p = Vec3::Random(-1, 1);
        real_t lensq = p.LengthSquared();
        if (kNormalizationEpsilon < lensq && lensq <= 1) return p / sqrt(lensq);
    }
}

inline Vec3 RandomOnHemisphere(const Vec3 &normal) {
    Vec3 onUnitSphere = RandomUnitVector();
    if (Dot(onUnitSphere, normal) > 0.0)
        return onUnitSphere;
    else
        return -onUnitSphere;
}

inline Vec3 Reflect(const Vec3 &v, const Vec3 &n) { return v - 2 * Dot(v, n) * n; }