#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "ray.h"
#include "hitable.h"

/*
 * A HitableList contains an array of pointers to Hitables.
 *
 * A HitableList's list field is a pointer to a pointer to a Hitable.
 * Said pointer to Hitable will be the first in the list of pointers.
 * 
 * Array indexing notation used to access list members.
 * list[0] will be a pointer to the first Hitable.
 * list[1] will be a pointer to the second Hitable.
 */

class HitableList : public Hitable {
    public:
        // Fields
        Hitable **list;
        int list_size;
        
        // Constructors
        HitableList() {}
        HitableList(Hitable **l, int n) { list = l; list_size = n; }
        
        // Inherited methods
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
};

/*
 * Returns true if ray r intersects with at least one of the hitable objects in this
 * HitableList and false otherwise.
 *
 * If the ray intersects with multiple objects, the closest intersection point to the
 * origin is used (smallest t value). This will be the ray's intersection with the
 * object most "in front" of the rendered scene, which is what makes sense to our eye.
 */
bool HitableList::hit(const Ray&r, float t_min, float t_max, hit_record& rec) const {
    bool hit_anything = false;
    float closest_so_far = t_max;
    hit_record temp_rec;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif /* HITABLE_LIST_H */