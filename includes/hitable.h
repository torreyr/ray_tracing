#ifndef HITABLE_H
#define HITABLE_H

#include "vec3.h"
#include "ray.h"

struct hit_record {
    float t;     // Position t along ray where ray intersects with hitable object.
    Vec3 p;      // Point along ray at position t. p = p(t) = A + Bt.
    Vec3 normal; // Normal unit vector for hitable object at point p.
};

/*
 * Abstract class all objects which rays can hit will implement.
 */

class Hitable {
    public:
        // Virtual methods
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* HITABLE_H */
