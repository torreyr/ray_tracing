#include <fstream>
#include <random>
#include <chrono>

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable.h"
#include "hitableList.h"
#include "camera.h"

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
    if (world->hit(r, 0.0, numeric_limits<float>::max(), rec)) {
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
    int nx = 200;   // columns of pixels
    int ny = 100;   // rows of pixels
    int ns = 100;   // number of antialiasing samples per pixel

    Hitable *list[2];
    Hitable *world = new HitableList(list, 2);
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);      // small sphere centered on the middle of the rendered plane
    list[1] = new Sphere(Vec3(0, -100.5, -1), 100); // large sphere centered way lower on the rendered plane

    Camera cam;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    ofstream of;
    of.open("./output/out.ppm");
    of << "P3\n" << nx << " " << ny << "\n255\n";

    // calculate color values for pixels
    // printed to file in the order moving from top to bottom, left to right
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);

            for (int s = 0; s < ns; s++) {
                float i_rand = generate_canonical<float, numeric_limits<float>::digits>(generator);
                float j_rand = generate_canonical<float, numeric_limits<float>::digits>(generator);

                float u = float(i + i_rand) / float(nx);    // convert pixel coords to camera coords, horizontal
                float v = float(j + j_rand) / float(ny);    // convert pixel coords to camera coords, vertical

                Ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);

            // convert from range 0.0-1.0 to range 0-255
            int ir = int(255.99 * col[0]);
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
