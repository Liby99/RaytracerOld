#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitive.h"

using namespace std;

class Ray;
class Intersection;

class Triangle : public Primitive {
    private:

        // Three vertices of the Triangle
        Vertex * v1;
        Vertex * v2;
        Vertex * v3;

        // The Need Interpolate Tag
        bool needInterpolate;
        vec3 getBaryCentric(vec3 position);
        vec3 interpolateNormal(vec3 position);
    public:
        Triangle(Scene * scene, mat4 transform, Vertex * v1, Vertex * v2, Vertex * v3, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shinness);
        virtual Intersection * intersect(Ray * ray);

        //getter method for creating bounding box
        virtual vector<vec3> getVertices();
        virtual vec3 getCenter();
        virtual bool intersectBox(vec3 minCorner, vec3 maxCorner);
};

#endif
