#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

/*
 * Inherits the Hitable class; a Sphere is a "hitable" object.
 *
 * Spheres have a
 *  - center point
 *  - radius
 */

class Sphere : public Hitable {
    public:
        // Fields
        Vec3 center;
        float radius;

        // Constructors
        Sphere() {}
        Sphere(Vec3 cen, float r) { center = cen; radius = r; }

        // Inherited methods
        virtual bool hit(const Ray&r, float t_min, float t_max, hit_record& rec) const;
};

/*
 * Returns true if ray r intersects with this sphere and false otherwise.
 *
 * Does this by calculating the square root part of the quadratic formula
 * (the discriminant). If that is negative, the equation has zero roots and
 * the ray does not intersect. Otherwise, if that is zero or positive, the
 * equation has one or two roots, respectively.
 *
 * If r intersects, the hit points are calculated. If either of those are
 * within the requeseted range (t_min < t < t_max), it is stored in the
 * provided hit_record.
 *
 * The normal vector for the sphere at the hit point is the vector from the
 * origin to that point on the sphere minus the vector from the origin to the
 * center of the sphere (0, 0, -1). Divide by radius of the sphere to make it
 * a unit vector.
 */
bool Sphere::hit(const Ray&r, float t_min, float t_max, hit_record& rec) const {
    Vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant >= 0) {
        // If there are two roots, we prefer the smaller one (closest hit point)
        float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        if (t1 > t_min && t1 < t_max) {
            // t1 is within requested range
            rec.t = t1;
            rec.p = r.point_at_parameter(t1);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        if (t2 > t_min && t2 < t_max) {
            // t2 is within requested range
            rec.t = t2;
            rec.p = r.point_at_parameter(t2);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif /* SPHERE_H */
