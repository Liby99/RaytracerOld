#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

using namespace std;

class Ray;
class Intersection;

class Sphere : public Primitive {
    private:

        // Basic properties of the sphere
        vec3 center;
        float radius;
        
    public:

        // Constructor
        Sphere(Scene * scene, mat4 transform, vec3 center, float radius, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shinness);
        virtual Intersection * intersect(Ray * ray);

        virtual vector<vec3> getVertices();
        virtual vec3 getCenter();
        virtual bool intersectBox(vec3 minCorner, vec3 maxCorner);
};

#endif
