#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera
{
    public:
    double aspect_ratio = 1.0 //ratio of image width over height
    int image_width = 100; //rendered image width in pixel count

    void render(const hittable& world)
    {
        intialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
        
    }

    private:

    int image_height; //rendered image height
    point3 center; //camera center/location of the coordinate system
    point pixel100_loc; //location of the pixel 0,0
    vec3 pixel_delta_u; //offset to pixel to the right
    vec3 pixel_delta_v ; //offset to pixel below

    color ray_color(const ray& r, const hittable& world) {
        hit_record rec;
        if (world.hit(r,interval(0,infinity) rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }
    
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
    
    void initialize()
    {
        i
    }

    color ray_color(const ray& r, const hittable& world) const{
        //
    }
};

#endif