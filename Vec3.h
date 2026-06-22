#pragma once

#include <cmath>
#include <iostream>

class Vec3 {
    public:
        // 1. Constructor
        Vec3() : e_{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}

        // 2. Getter/Setter
        double x() const {return e_[0];}
        double y() const {return e_[1];}
        double z() const {return e_[2];}

        // 3. Member functions
        double Length() {
            return std::sqrt(LengthSquared());
        }
        double LengthSquared() {
            return e_[0]*e_[0] + e_[1]*e_[1] + e_[2]*e_[2];
        }

        // 4. Operators
        Vec3 operator-() const { return Vec3(-e_[0], -e_[1], -e_[2]); }
        double operator[](int i) const { return e_[i]; }
        double& operator[](int i) { return e_[i]; }

        Vec3& operator+=(const Vec3& v) {
            e_[0] += v.e_[0];
            e_[1] += v.e_[1];
            e_[2] += v.e_[2];
            return *this;
        }

        Vec3& operator*=(double t) {
            e_[0] *= t;
            e_[1] *= t;
            e_[2] *= t;
            return *this;
        }

        Vec3& operator/=(double t) {
            return *this *= 1/t;
        }

    private:
        // 5. Member variables
        double e_[3];
};

using Point3 = Vec3; // 3D point (just an alias)

// Vec3 Utility Functions