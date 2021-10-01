#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
 * Think of a ray as the function p(t) = A + Bt.
 *  - p is the position along that line
 *  - A is the ray origin
 *  - B is the ray direction
 */

class Ray {
    Vec3 A;
    Vec3 B;
    
    public:
        // Constructors
        Ray() {}
        Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }
        
        // Methods
        Vec3 origin() const { return A; }
        Vec3 direction() const { return B; }
        Vec3 point_at_parameter(float t) const { return A + t*B; }
};

#endif /* RAY_H */
