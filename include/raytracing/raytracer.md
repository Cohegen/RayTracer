# But what is a raytracer?
- A ray tracer at its core just sends rays through pixels and computes the color seen in the direction of those rays.
- It follows the following steps:
         1. Calculate the ray from the "eye" through the pixel.
         2. Determine which objects the ray intersects .
         3. Computes a color for the closest intersection point.

## Deep dive
- Let's consider an image 800 pixels wide by 400 pixels high.
- To get the image's aspect ratio we divide the width by height.
- So an image the aspect ratio is:
```
aspect ratio = width /height
```     
- Having an image's aspect ratio can come in handly, since let's say we're given an image's width and aspect ratio, we can use these data to calculate its height.

- Also, in the process of setting up the pixel dimensions for the rendered image, we also need to set up a virtual **viewport** through which the scene rays are passed.
- The viewport is a virtual rectangle in the 3D world that contains the grid of image pixel locations.
- If the pixels are spaced the same distance horizontally as they are vertically, the viewport that bounds them will have the same aspect ratio as the rendered image.
- The distance between adjacent pixels is called the **pixel spacing** and square pixels is the standard.
- Take the code below:
```
auto aspect_ratio = 16.0 /9.0;
int image_width = 400;

//calculating the image height, and also ensuring that it's at least 1
int image_height = int(image_width / aspect_ratio);
image_height = (image_height < 1) ? 1 : image_height;

//viewport width
auto viewport_height = 2.0;
auto viewport_width = viewport_height * (double(image_width)/image_height);
```
- The code above defines our camera view.
- We first calculate the aspect ratio:
```
auto aspect_ratio = 16.0 / 9.0;

```
- We then compute the size of the image height by:
```
int image_height = int(image_width/aspect_ratio);

```
- And if say our image_height is less than or equal to 0 we set it to 1 using the expression below:
```
image_height = (image_height <1) ? 1: image_height;
```
- We then compute the size of our viewport's width using the expression below:
```
auto viewport_width = viewport_height * (double(image_width)/image_height);
```

- We then define the camera's center i.e a point in 3D space from which all scene rays will originate (eye point).
- The vector from the camera center to the viewport center will be orthogonal to the viewport.
- We can set the distance between the viewport and the camera center point to be one unit.
- This distance is often referrd to as the focal length.

## Camera Coordinate system
- Here the camera center is at (0,0,0), i.e y up,x right , negative z forward.

- Z is negative because this coordinate system is right-handed.

- In maths y increases **upwards** but in images it increases downwards as top-left is (0,0)
- So in image pixels going down = + y

### Scanning the image
- We start at (0,0) and go left to right and the top to bottom.
- so the pixels are visited like this :
```
(0,0) → (1,0) → (2,0) ...
↓
(0,1) → (1,1) → ...
```
- This is known as the **standard raster scan**.

### The viewport
- As we saw earlier the viewport is an invisible rectangle floating infront of our camera
- We define two important vectors:
        1. Vu(viewport_u) : it goes left to right and it represents the full width of the viewport.
        2. Vv(viewport_v): goes top to bottom. It represents the full height of the viewport i.e vertical direction.

- Since the image Y goes downwards, Vv points downward in 3D space and not upward like in maths.

### Pixel grid inside the viewport
- Here the pixel gird will be inset from the viewport edges by half the pixel distance.
- Why do we do this?
- We do this because each pixel in the grid represents an area not a point.
- Instead of shooting rays from the pixel corners, we shoot from the pixel centers.
- So by this we mean that:
    - The first pixel is not exactly at the edge
    - It's shifted half a pixel inward.

## Definitions
1. Q (viewport upper-left corner) - starting point of the viewport in 3D space.
2. P_0,0(first pixel center) - slightly offset from Q (by half a pixel in both directions).
3. delta_u - step from one pixel to the next horizontally.
4. delta_v - step from one pixel to the next vertically.

# 2 Adding a Sphere
- Spheres are often used in ray tracers because calculating whether a ray hits a sphere is relatively simple.

## 2.1 Ray-Sphere Intersection
- The equation of a sphere of radius **r** is given is:
```
x**2 + y**2  + z**2 = r**2
```
-If we want to allows the sphere center to be at a randomly choosen point (Cx,Cy,Cz),then the equation will look like this:
```
(Cx-x)**2 + (Cy-y)**2 + (Cz-z)**2 = r**2
```
- In graphics, we want the formula to be in terms of vectors, which are represented using **vec3** class.
- So we notice than the vector from point **P** = **(x,y,z)** to Center **C** = **(Cx,Cy,Cz)** is **(C-P)**.
- If we use the definition of the dot product:
```
(C-P)*(C-P) = (Cx-x)**2 + (Cy-y)**2 + (Cz-z)**2
```
- Then we can write the equation of the sphere in vector form as:
```
(C-P)*(C-P) = r**2
```

- So for any point **P** that satisfies this equation on  the sphere.
- We are required to know if our ray **P(t) = Q + td** ever hits the sphere anywhere.
- If it does hit the sphere, there is some **t** for which **P(t)** satisfies the sphere equation.
- So we are now looking for any **t** where it is true:
```
(C-P(t))*(C-P(t)) = r**2
```
which can be found by replacing **P(t)** with its expanded form:
```
(C-(Q+td))*(C-(Q+td)) = r**2

```
- Since we want to solve for **t**, we seperate the terms based on whether there is a **t** or not:
```
(-td+(C-Q))*(-td+(C-Q)) = r**2
```
- We can follow the rules of vector algebra to distribute the dot product:
```
(t**2)*d*d - 2td * (C-Q) + (C-Q) * (C-Q) = r**2
```
- After multiplication all our vector will be reduced to scalars by dot product.
- So we use the quadratic formula to find **t**.
- So for solving **t**, the ray-sphere intersection equation gives us these values for **a**, **b** and **c**:
```
a = d*d
b = -2d*(C-Q)
c = (C-Q)*(C-Q) - r**2
```
- So if we get no  real roots (negative roots) it means the ray doesn't intersect with sphere.
- And we we get a root that equal to zero it mean the ray only hits the sphere and doesn't exit.
- If the root is greater than zero it means that the ray hits the sphere and exits.

# 3 Surface Normals and Multiple Objects


## 3.1 Shading with Surface Normals
- A surface normal vector  is a vector that is perpendicular to the surface at the point of the intersection.

- There three important observations made here:
    1. If a unit-length normal vector is required, then we might do it up front once, instead of repeating in over and over again. i.e normalizing it once instead of normalizing it everywhere.
    2. We do require unit-length normal vectors in several places.
    3. If we require normal vectors to be unit length. We do this by say given sphere normals, these normals can be made unit length by simply dividing by sphere radius avoiding the square root entirely.

- For a sphere:
- Normal is :
```
N = P - C
```
- But P is on the sphere.
- So |P-C| = r
- So the unit normal vector becomes:
```
N^ = (P - C) /r
```

### Simplifying the Ray-Sphere Intersection equation
- We can recall that a vector dotted with itself is equal to the squared length of the vector.
- The we can see that the equation for **b** has a factor of negative two in it.
- If b= - 2h , then :
- ### Simplification of the Quadratic Formula

Given the standard quadratic formula:
$$\frac{-b \pm \sqrt{b^2 - 4ac}}{2a}$$

Substituting $b = -2h$:
$$\frac{-(-2h) \pm \sqrt{(-2h)^2 - 4ac}}{2a}$$

Expanding the square inside the radical:
$$\frac{2h \pm \sqrt{4h^2 - 4ac}}{2a}$$

Factoring out the $4$ ($\sqrt{4} = 2$):
$$\frac{2h \pm 2\sqrt{h^2 - ac}}{2a}$$

Final simplified form:
$$\frac{h \pm \sqrt{h^2 - ac}}{a}$$
