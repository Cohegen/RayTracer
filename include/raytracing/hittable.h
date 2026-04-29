/*
Here we define an abstract class which has a hit function
that takes in a ray
It also includes valid intervals for hits i.e
t_min to t_max, so the hit only "counts" if t_min < t < t_max.

*/
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

using rt::dot;

class hit_record
{
    public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r,const vec3& outward_normal)
    {
        //sets the hit record normal vector
        // the outward normal is assumed to have unit length i.e magnitude of 1
        front_face = dot(r.direction(),outward_normal) < 0;
        normal = front_face ? outward_normal : - outward_normal;
    }
};

class hittable
{
    public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double ray_tmin,double ray_tmax, hit_record& rec) const = 0;
};


#endif