#include "raytracing/color.h"
#include "raytracing/constant.h"
#include "raytracing/hittable.h"
#include "raytracing/hittable_list.h"
#include "raytracing/ray.h"
#include "raytracing/sphere.h"
#include "raytracing/vec3.h"

#include <iostream>
#include <limits>
#include <random>

using rt::color;
using rt::point3;
using rt::unit_vector;
using rt::vec3;
using rt::write_color;

double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

vec3 random_vec3(double min, double max) {
    return vec3(
        min + (max - min) * random_double(),
        min + (max - min) * random_double(),
        min + (max - min) * random_double()
    );
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = random_vec3(-1.0, 1.0);
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

color ray_color(const ray& r, int depth, const hittable& world) {
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec)) {
        vec3 direction = rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 50;
    int max_depth = 10;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);

            for (int sample = 0; sample < samples_per_pixel; sample++) {
                auto pixel_sample = pixel00_loc
                                  + ((i + random_double()) * pixel_delta_u)
                                  + ((j + random_double()) * pixel_delta_v);
                auto ray_direction = pixel_sample - camera_center;
                ray r(camera_center, ray_direction);

                pixel_color += ray_color(r, max_depth, world);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::clog << "\rDone.                 \n";
    return 0;
}
