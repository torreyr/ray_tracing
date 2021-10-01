#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitableList.h"

using namespace std;

/*
 * Takes a Ray and a list of all hitable objects and returns a Vec3 color 
 * that should be at that point.
 * If the ray intersects with an object in the list,
 *  - Get the normal unit vector from the returned hit_record
 *  - Add one to the normal and divide by two to make all the elements in
 *    the range [0,1]
 *  - Return this new vector as the color value
 * Otherwise,
 *  - Get the direction vector of the ray and convert it to a unit vector
 *  - Convert the y available coordinate range from [-1,1] to [0,1]
 *  - Calculate and return a color value between white and blue based on
 *    the y coordinate
 */
Vec3 color(const Ray& r, Hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    } else {
        Vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

/*
 * PPM is Portable Pixmap Format (file encoding)
 * This function prints the RGB values of a PPM file to the console.
 */
void printPPM() {
    int nx = 200;   // columns
    int ny = 100;   // rows
    
    // Using 50 pixels per coordinate unit.
    Vec3 origin(0.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);               // total vertical distance
    Vec3 horizontal(4.0, 0.0, 0.0);             // total horizontal distance
    Vec3 lower_left_corner(-2.0, -1.0, -1.0);
    
    Hitable *list[2];
    Hitable *world = new HitableList(list, 2);
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);      // small sphere centered on the middle of the rendered plane
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100); // large sphere centered way lower on the rendered plane
    
    ofstream of;
    of.open("./output/out.ppm");
    of << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);     // color moving from left edge to right edge
            float v = float(j) / float(ny);     // color moving from top edge to bottom edge
            
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical);   // create a ray from the origin to the pixel
            Vec3 col = color(r, world);                                     // calculate the color for the ray
            
            int ir = int(255.99 * col[0]);      // convert from range 0.0-1.0 to range 0-255
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            of << ir << " " << ig << " " << ib << "\n";
        }
    }
    of.close();
}

int main() {
    printPPM();
    return 0;
}
