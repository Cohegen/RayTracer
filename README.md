# RayTracer

A small C++20 ray tracing starter project built with CMake.

This project implements a basic ray tracer following the "Ray Tracing in One Weekend" series concepts. It currently renders a scene with multiple spheres and a gradient background, using surface normals for basic shading.

![Latest Render](assets/viewport2.png)

## Core Concepts Covered

### 1. Rays, Camera, and Background
The core of the ray tracer sends rays through each pixel of an image and calculates the color seen in that direction.
- **Ray Class**: Represents a line in 3D space with an origin and direction.
- **Camera Model**: A simple pinhole camera centered at the origin $(0,0,0)$ looking towards the negative Z-axis.
- **Viewport**: A virtual rectangle in 3D space through which rays are cast. The viewport aspect ratio matches the image aspect ratio.
- **Background**: A simple vertical linear gradient (lerp) from white to light blue, simulating a sky.

### 2. Vector Math (`vec3`)
Almost everything in ray tracing uses 3D vectors. Our `vec3` class handles:
- **Points**: Locations in 3D space.
- **Colors**: RGB values.
- **Geometric Vectors**: Directions, normals, and offsets.
- **Operations**: Addition, subtraction, scalar multiplication, dot products, and cross products.

### 3. Ray-Sphere Intersection
Determining if a ray hits a sphere involves solving a quadratic equation derived from the sphere's geometric definition:
$$(P - C) \cdot (P - C) = r^2$$
Substituting the ray equation $P(t) = Q + t\mathbf{d}$ gives a quadratic in $t$. The discriminant of this equation tells us if the ray hits the sphere.

### 4. Surface Normals and Shading
To give objects a 3D appearance, we use surface normals (vectors perpendicular to the surface at the hit point).
- **Normals**: For a sphere, the normal is simply the vector from the center to the hit point.
- **Normal Shading**: We visualize normals by mapping their $x, y, z$ components to RGB colors, which helps in debugging geometry and light interaction.

### 5. Hittable Objects and Lists
The project uses an abstraction layer to handle multiple objects in a scene:
- **`hittable`**: An abstract base class for any object a ray can intersect.
- **`sphere`**: A concrete implementation of a `hittable` sphere.
- **`hittable_list`**: A container that holds multiple `hittable` objects and finds the closest intersection for any given ray.

## Project Structure

```text
RayTracing/
|-- include/
|   `-- raytracing/
|       |-- color.h          # Color utility and PPM output
|       |-- constant.h       # Mathematical constants (e.g., infinity)
|       |-- hittable.h       # Abstract base class for hit detection
|       |-- hittable_list.h  # Container for scene objects
|       |-- ray.h            # Ray class definition
|       |-- sphere.h         # Sphere object implementation
|       `-- vec3.h           # 3D vector and math utilities
|-- src/
|   `-- main.cpp             # Main render loop and scene setup
|-- assets/                  # Rendered image samples
|-- CMakeLists.txt           # Build configuration
`-- README.md                # This file
```

## Prerequisites

- CMake 3.20 or newer
- A C++20-capable compiler (MSVC, Clang, or GCC/MinGW)

## Build and Run

```powershell
# Configure and Build
cmake -S . -B build
cmake --build build --config Release

# Run (outputs PPM data to stdout)
.\build\bin\raytracing > output.ppm
```

## Current Status
- [x] Basic `vec3` and `ray` classes.
- [x] Camera and viewport setup.
- [x] Sphere intersection logic.
- [x] Surface normal visualization.
- [x] Support for multiple objects (`hittable_list`).
- [ ] Antialiasing (MSAA).
- [ ] Diffuse materials (Lambertian).
- [ ] Metal and Dielectric materials.
