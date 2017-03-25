#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include "Vertex.h"
#include "Ray.h"

using namespace std;

class Scene;
class Ray;
class Intersection;

class Primitive {
    protected:

        // Reference to the scene
        Scene * scene;

        // Transformation matrix
        mat4 transform;

        // The Lighting References
        vec3 diffuse;
        vec3 specular;
        vec3 emission;
        vec3 ambient;
        float shininess;
    public:

        // Basic Constructor
        Primitive(Scene * scene, mat4 transform, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shininess);

        // Get the Intersection with the ray
        virtual Intersection * intersect(Ray * ray);
        virtual vec3 getDiffuse();
        virtual vec3 getSpecular();
        virtual vec3 getEmission();
        virtual vec3 getAmbient();
        virtual float getShininess();

        virtual vector<vec3> getVertices();
        virtual vec3 getCenter();
        virtual bool intersectBox(vec3 minCorner, vec3 maxCorner);
};

#endif
