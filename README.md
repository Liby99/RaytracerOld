# Ray Tracer

## About

A simple Ray Tracer that will take in a plain text scene file and export an
image according to the scene file.

Author: Ziyang Li ([@Liby99](https://github.com/Liby99)), Yunlu Huang ([@Ahuang](https://github.com/YunluHuang))

## Compiling

```
$ make
```

## Running

```
$ ./raytrace [scenefile]
```

## Scene File Syntax

You may want to write the scene file yourself. And here is the syntax of the
scene file so that you can write it.

### Image Size

The first thing you want to set up in the scene file is the size of the image,
which has a syntax like this:

```
size 600 400
```

This will generate a 600 x 400 image (width 600, height 400) in the end

### Output Image File Name

You must specify the name of the output file. The syntax is

```
output YOUR_FILE_NAME.png
```

So the final png file will be outputted using `YOUR_FILE_NAME.png`.

### Camera

You definitely want to set up the camera. The Syntax is

```
camera 3 3 3   0 0 0   0 1 0   60.0
#      -----   -----   -----   ----
#       eye    centr    up     fovy
```

Though looks very complicated, it's actually very straightforward. There are 10
arguments in total, which contains 4 parts: eye vector, center vector, up vector
and field of view degree.

- `eye`: The position of the camera
- `centr`: The point that the camera is looking at
- `up`: The up direction of the camera
- `fovy`: The degree of field of view in the **y** direction

Here in the example we have camera located in (3, 3, 3), looking towards the
origin (0, 0, 0), with up vector the y direction (0, 1, 0), and finally with
a field of view of 60 degrees.

### Light

**TODO**

### Vertex

There are two kinds of vertices: one with normal and one without normal. The
with normal one will be helpful in rendering non-flat triangles. The vertices
will be used in creating triangles. And the order of vertices matters

To generate simple vertex, use

```
vertex 1 1 1
```

This will get you a vertex (1, 1, 1).

To generate vertex with normal, use

```
vertexnormal 1 1 1 0 1 0
```

This will generate a vertex (1, 1, 1) with normal (0, 1, 0)

### Triangle

There are also two kinds of triangles: one with normal specified and one
without normal. The one with normal, when rendering, will be interpolated to
generate intermediate normal based on barycentric coordinates.

To generate a simple triangle, use

```
tri 0 1 2
```

where the trailing numbers are the indices of the vertices in the order they
are added. When using the simple `tri`, even if the all the vertices have
normals, the interpolation process is forced closed.

To generate a triangle that will be interpolated using the vertex normal, use

```
trinormal 0 1 2
```

The arguments are the same as previous. If the vertices have normals, then it
will be interpolated using the normals. But if a vertex doesn't have normal,
then it's normal will be assigned to the normal of the triangle plane.

### Sphere

**TODO**

### Cube

**TODO**

### Animation

You can now add Animation System into the raytracer. It will rotate the camera by
y-axis for 360 degrees, which will generate 72 png images each rotates 5 degrees.

You must specify that the raytracer is going to export animation in the scenefile
like this:

```
size 400 600
camera 0 2 2 0 0 0 0 1 0 60
output animation/output
animate # <- THIS LINNNNNNNNNNNNNNNNNNNE
```

Then it will automatically generate 72 images under `animation` folder with name
`output01.png`, `output02.png`, `output03.png` up until `output72.png`.
