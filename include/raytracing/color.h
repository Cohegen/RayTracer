#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "raytracing/vec3.h"

#include <algorithm>
#include <ostream>

namespace rt {

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color) {
    const double r = std::clamp(pixel_color.x(), 0.0, 1.0);
    const double g = std::clamp(pixel_color.y(), 0.0, 1.0);
    const double b = std::clamp(pixel_color.z(), 0.0, 1.0);

    const int rbyte = static_cast<int>(255.999 * r);
    const int gbyte = static_cast<int>(255.999 * g);
    const int bbyte = static_cast<int>(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

} // namespace rt

#endif
