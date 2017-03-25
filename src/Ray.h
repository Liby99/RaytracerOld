#ifndef RAY_H
#define RAY_H

#include <vector>
#include "Transform.h"
#include "Intersection.h"

using namespace std;

class Scene;
class Intersection;
class BvhNode;

class Ray {
    private:
        
        // Basic property of a Ray
        Scene * scene;
        vec3 origin;
        vec3 direction;
        int depth;
        
        // Basic Setters
        void setScene(Scene * scene);
        void setOrigin(vec3 origin);
        void setDirection(vec3 direction);
        
        // Helper Methods in getting color
        vec3 getLightingColor();
        vec3 getReflectingColor();
        
        // Helper Method of getting intersection
        void getIntersectionsHelper(BvhNode * node, vector<Intersection *> & intersections);
        bool hasIntersectionHelper(BvhNode * node);
    public:
        
        // Constructor
        Ray(Scene * scene, vec3 source, vec3 direction);
        Ray(Scene * scene, vec3 source, vec3 direction, int depth);
        
        int getDepth();
        
        // Basic Getters
        void setDepth(int depth);
        vec3 getOrigin();
        vec3 getDirection();
        
        // Get all the intersections with the ray
        bool hasIntersection();
        vector<Intersection *> getIntersections();
        
        // Directly get the ray color
        vec3 getColor();
};

#endif
