#ifndef CUBE_H
#define CUBE_H

#include "Primitive.h"

using namespace std;

class Ray;
class Intersection;

class Cube : public Primitive {
    private:
        vec3 center;
        float side;
    public:
        Cube(Scene * scene, mat4 transform, vec3 center, float side, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shinifness);
        virtual Intersection * intersect(Ray * ray);
};

#endif
