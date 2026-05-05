/*
Here we define our constants

*/
#ifndef CONSTANT_H
#define CONSTANT_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

//C++ std Usings
using std::make_shared;
using std::shared_ptr;

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi =3.1415926535897932385;

//utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees* pi /180.0;
}

//Common headers
#include "raytracing/color.h"
#include "raytracing/ray.h"
#include "raytracing/vec3.h"
#include "raytracing/interval.h"

#endif