#pragma once

#include "Interval.h"
#include "Ray.h"
#include "Vec3.h"

class Aabb {
  public:
    static const Aabb empty, universe;

    Aabb() {}
    Aabb(const Interval &x, const Interval &y, const Interval &z) : x_(x), y_(y), z_(z) {}
    Aabb(const Point3 &a, const Point3 &b) {
        // a, b = extremas
        x_ = (a[0] <= b[0]) ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
        y_ = (a[1] <= b[1]) ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
        z_ = (a[2] <= b[2]) ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
    }
    Aabb(const Aabb &box0, const Aabb &box1) {
        x_ = Interval(box0.x_, box1.x_);
        y_ = Interval(box0.y_, box1.y_);
        z_ = Interval(box0.z_, box1.z_);
    }

    const Interval &AxisInterval(int n) const {
        if (n == 1) return y_;
        if (n == 2) return z_;
        return x_;
    }

    bool Hit(const Ray &r, Interval rayT) const {
        const Point3 &rayOrig = r.orig();
        const Vec3 &rayDir = r.dir();

        for (int axis = 0; axis < 3; axis++) {
            const Interval &ax = AxisInterval(axis);
            const real_t adinv = 1.0 / rayDir[axis]; // axis direction inverse

            real_t t0 = (ax.min() - rayOrig[axis]) * adinv;
            real_t t1 = (ax.max() - rayOrig[axis]) * adinv;

            if (t0 < t1) {
                if (t0 > rayT.min()) rayT.min(t0);
                if (t1 < rayT.max()) rayT.max(t1);
            } else {
                if (t1 > rayT.min()) rayT.min(t1);
                if (t0 < rayT.max()) rayT.max(t0);
            }

            if (rayT.max() <= rayT.min()) return false;
        }
        return true;
    }

    int LongestAxis() const {
        if (x_.Size() > y_.Size())
            return x_.Size() > z_.Size() ? 0 : 2;
        else
            return y_.Size() > z_.Size() ? 1 : 2;
    }

  private:
    Interval x_, y_, z_;
};

const Aabb Aabb::empty = Aabb(Interval::empty, Interval::empty, Interval::empty);
const Aabb Aabb::universe = Aabb(Interval::universe, Interval::universe, Interval::universe);