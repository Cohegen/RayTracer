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
2. $\P_{0,0}$