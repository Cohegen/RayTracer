#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "raytracing/vec3.h"

#include <algorithm>
#include <cmath>
#include <ostream>

namespace rt {

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    return linear_component > 0.0 ? std::sqrt(linear_component) : 0.0;
}

inline void write_color(std::ostream& out, const color& pixel_color, int samples_per_pixel = 1) {
    const double scale = 1.0 / samples_per_pixel;
    const double r = std::clamp(linear_to_gamma(scale * pixel_color.x()), 0.0, 0.999);
    const double g = std::clamp(linear_to_gamma(scale * pixel_color.y()), 0.0, 0.999);
    const double b = std::clamp(linear_to_gamma(scale * pixel_color.z()), 0.0, 0.999);

    const int rbyte = static_cast<int>(256 * r);
    const int gbyte = static_cast<int>(256 * g);
    const int bbyte = static_cast<int>(256 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

} // namespace rt

#endif
