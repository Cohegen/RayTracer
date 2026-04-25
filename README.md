# RayTracing

A small C++20 ray tracing starter project built with CMake.

Right now the project renders a simple gradient image to `output/image.ppm`. The repository is structured so it can grow cleanly into a real ray tracer with additional files for rays, cameras, hittable objects, materials, and scene setup.

## Prerequisites

- CMake 3.20 or newer
- A C++20-capable compiler such as MSVC, Clang, or GCC/MinGW

## Project Structure

```text
RayTracing/
|-- include/
|   `-- raytracing/
|       |-- color.h
|       `-- vec3.h
|-- output/
|-- src/
|   `-- main.cpp
|-- .gitignore
|-- CMakeLists.txt
`-- README.md
```

## Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

## Run

```powershell
.\build\bin\raytracing.exe
```

For multi-config generators such as Visual Studio, the executable may be placed under a configuration subdirectory such as `build\bin\Release\raytracing.exe`.

## Current Status

- `vec3` math utilities live in `include/raytracing/vec3.h`
- color output helpers live in `include/raytracing/color.h`
- the program entry point is `src/main.cpp`
- rendered images are written to `output/`

## Suggested Next Steps

1. Add a `ray` class.
2. Add a camera that emits rays through the viewport.
3. Add sphere intersection logic.
4. Render a sky gradient through ray tracing instead of direct pixel coloring.
5. Add materials and multiple objects.
