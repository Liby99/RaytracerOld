#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include "Transform.h"
#include "Ray.h"

using namespace std;

class Scene;
class Primitive;
class Ray;
class PointLight;
class DirectionalLight;

class Intersection {
    private:
        
        const static float INCREMENT;
        
        // References to Scene, Ray and Object Related to this Intersection
        Scene * scene;
        Ray * ray;
        Primitive * object;
        
        // Paramaters corresponding to this intersection
        bool hitFlag; // Whether the intersection hit an object
        vec3 intersect; // If intersects, then there is a position
        vec3 normal; // Also a Normal vector
        float t; // The result t of the equation p = p0 + t * p1
        
        // Get Light Color Helper Method
        static vec3 getLightingColorHelper(vec3 lightness, vec3 diffuse, vec3 normal, vec3 direction, vec3 specular, vec3 halfAngle, float shininess);
        vec3 getPointLightingColor(PointLight * pLight);
        vec3 getDirectionalLightingColor(DirectionalLight * dLight);
        
        // Setter
        void setScene(Scene * scene);
        void setRay(Ray * ray);
        void setObject(Primitive * object);
        
        //
        vec3 getLightingColor();
        vec3 getReflectingColor();
    public:
        
        // Constructor
        Intersection(Scene * scene, Ray * ray, Primitive * object);
        
        // Basic Setters
        void setHit(bool hit);
        void setT(float t);
        void setNormal(vec3 normal);
        
        // Basic Getters
        bool hit();
        vec3 getIntersect();
        vec3 getNormal();
        Primitive * getObject();
        
        void setIntersect(vec3 intersect);
        void applyTransformation(mat4 transform);
        
        // Get the distance to the ray source
        float getDistanceToOrigin();
        
        // Directly Get The
        vec3 getColor();
};

#endif
