#include "raytracing/color.h"

#include <filesystem>
#include <fstream>
#include <iostream>

int main() {
    constexpr int image_width = 256;
    constexpr int image_height = 256;

    const std::filesystem::path output_dir = "output";
    const std::filesystem::path output_file = output_dir / "image.ppm";

    std::filesystem::create_directories(output_dir);

    std::ofstream out(output_file, std::ios::out | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: could not open output file " << output_file.string() << '\n';
        return 1;
    }

    out << "P3\n"
        << image_width << ' ' << image_height
        << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::clog << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            const double r = static_cast<double>(i) / (image_width - 1);
            const double g = static_cast<double>(j) / (image_height - 1);
            const double b = 0.0;

            const rt::color pixel_color(r, g, b);
            rt::write_color(out, pixel_color);
        }
    }

    std::clog << "\rDone. Wrote " << output_file.string() << "            \n";
    return 0;
}
