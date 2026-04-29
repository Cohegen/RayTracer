/*
- A ray is a line that starts at a point and goes infinitely in one direction.

This program defines a ray class
Which is defined as a function P(t) = A + tb
Where:
    - P is a 3D position along a line in 3D.
    - A is the ray origin.
    - b is the ray direction.
    - t is is real number
- When we plug in t, P(t) moves the point along the ray.
When position t is plugged in we get only the parts in front of A, 
*/

#ifndef RAY_H 
#define RAY_H 

#include "vec3.h"

using rt::point3;
using rt::vec3;

class ray 
{
public:
    ray(){}

    ray(const point3& origin,const vec3& direction): orig(origin),dir(direction){}

    const point3& origin() const {return orig;}
    const vec3& direction() const {return dir;}

    point3 at(double t) const {
        return orig + t*dir;
    }

private:
     point3 orig;
     vec3 dir;

};

#endif 