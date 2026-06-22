#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
    public:
        Vec3() : e_{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}

        double x() const {return e_[0];}
        double y() const {return e_[1];}
        double z() const {return e_[2];}

        Vec3 operator-() const {return Vec3(-e_[0], -e_[1], -e_[2]);}
        double operator[](int i) const {return e_[i];}
        double& operator[](int i) {return e_[i];}

        // Vector addition
        Vec3& operator+=(const Vec3 &v) {
            e_[0] += v.e_[0];
            e_[1] += v.e_[1];
            e_[2] += v.e_[2];
            return *this;
        }

        // Scalar multiplication
        Vec3& operator*=(const double t) {
            e_[0] *= t;
            e_[1] *= t;
            e_[2] *= t;
            return *this;
        }

        // Scalar division
        Vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        // Vector length
        double length() const {
            return std::sqrt(length_squared());
        }

        // Vector length squared
        double length_squared() const {
            return e_[0]*e_[0] + e_[1]*e_[1] + e_[2]*e_[2];
        }   

    public:
        double e_[3];
};