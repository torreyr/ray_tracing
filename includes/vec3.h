#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>

/*
 * A Vec3 can be used for colors, locations, directions, offsets, etc.
 *
 * When defining a COLOR:
 *  - e0 is the red value
 *  - e1 is the green value
 *  - e2 is the blue value
 *
 * When defining a LOCATION:
 * These represent the endpoint of the vector, the start point being
 * the origin, which is the camera/eye position.
 *  - e0 is the X coordinate
 *  - e1 is the Y coordinate
 *  - e2 is the Z coordinate
 */

class Vec3 {
    public:
        // Fields
        float e[3];

        // Constructors
        Vec3() {}
        Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

        // Components
        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }
        inline float z() const { return e[2]; }
        inline float r() const { return e[0]; }
        inline float g() const { return e[1]; }
        inline float b() const { return e[2]; }

        // Operator overloading
        inline float operator[](int i) const { return e[i]; }
        inline float& operator[](int i) { return e[i]; }
        inline Vec3& operator+=(const Vec3 &v);
        inline Vec3& operator/=(const float f);

        // Methods
        inline float length() const {
            return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        }
};

//
// OPERATOR OVERLOADING - MEMBER FUNCTIONS
//

inline Vec3& Vec3::operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const float f) {
    e[0] /= f;
    e[1] /= f;
    e[2] /= f;
    return *this;
}

//
// OPERATOR OVERLOADING - NON-MEMBER FUNCTIONS
//

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 v1, const Vec3 &v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(float t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(Vec3 v, float t) {
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

//
// FUNCTIONS
//

inline Vec3 unit_vector(const Vec3 v) {
    return v / v.length();
}

inline float dot(const Vec3 v1, const Vec3 v2) {
    return (v1.e[0] * v2.e[0]) + (v1.e[1] * v2.e[1]) + (v1.e[2] * v2.e[2]);
}

#endif /* VEC3_H */
