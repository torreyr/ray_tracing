#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

/*
 * A camera, or viewpoint, with a position (origin) and viewport
 * properties.
 *  - vertical is a direction vector spanning the image in the y-axis
 *  - horizontal is a direction vector spanning the image in the x-axis
 *  - lower_left_corner is the point in our coordinate system where
 *    pixel [0,0] exists
 */

class Camera {
    public:
        // Fields
        Vec3 origin;
        Vec3 vertical;
        Vec3 horizontal;
        Vec3 lower_left_corner;

        // Constructors
        Camera() {
            origin = Vec3(0.0, 0.0, 0.0);
            vertical = Vec3(0.0, 2.0, 0.0);
            horizontal = Vec3(4.0, 0.0, 0.0);
            lower_left_corner = Vec3(-2.0, -1.0, -1.0);
        }

        // Methods
        Ray get_ray(float u, float v);
};

/*
 * Returns a Ray going from the camera origin to the specified pixel.
 *  - u is the pixel's horizontal column value (0 at left)
 *  - v is the pixel's vertical row value (0 at bottom)
 */
Ray Camera::get_ray(float u, float v) {
    return Ray(origin, lower_left_corner + u*horizontal + v*vertical);
}

#endif /* CAMERA_H */
