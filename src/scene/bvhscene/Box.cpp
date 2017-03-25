#include "Box.h"
#include "Ray.h"

using namespace std;

Box::Box() {
    hasObj = false;
}

Box::Box(Primitive * obj) {
    vector<vec3> vertices = obj->getVertices();
    minCorner = vertices[0];
    maxCorner = vertices[0];
    for(int i = 0; i < vertices.size(); i++) {
        minCorner.x = min(minCorner.x, vertices[i].x);
        minCorner.y = min(minCorner.y, vertices[i].y);
        minCorner.z = min(minCorner.z, vertices[i].z);
        maxCorner.x = max(maxCorner.x, vertices[i].x);
        maxCorner.y = max(maxCorner.y, vertices[i].y);
        maxCorner.z = max(maxCorner.z, vertices[i].z);
    }
    hasObj = true;
}


Box::Box(vector<Primitive*> & objs) {
    hasObj = false;
    for(int i = 0; i < objs.size(); i++) {
        this->extend(objs[i]);
    }
}


Box::Box(vec3 minCorner, vec3 maxCorner) {
    this->minCorner = minCorner;
    this->maxCorner = maxCorner;
}

void Box::extend(Primitive * obj) {
    vector<vec3> vertices = obj->getVertices();
    if(hasObj == false) {
        minCorner = vertices[0];
        maxCorner = vertices[0];
    }
    for (int i = 0; i < vertices.size(); i++) {
        minCorner.x = min(minCorner.x, vertices[i].x);
        minCorner.y = min(minCorner.y, vertices[i].y);
        minCorner.z = min(minCorner.z, vertices[i].z);
        maxCorner.x = max(maxCorner.x, vertices[i].x);
        maxCorner.y = max(maxCorner.y, vertices[i].y);
        maxCorner.z = max(maxCorner.z, vertices[i].z);
    }
    hasObj = true;
}

Box * Box::combine(Box * box1, Box * box2) {
    vec3 min1 = box1->getMinCorner();
    vec3 min2 = box2->getMinCorner();
    vec3 max1 = box1->getMaxCorner();
    vec3 max2 = box2->getMaxCorner();

    vec3 newMinCorner = vec3(min(min1.x, min2.x), min(min1.y, min2.y), min(min1.z, min2.z));
    vec3 newMaxCorner = vec3(max(max1.x, max2.x), max(max1.y, max2.y), max(max1.z, max2.z));
    Box * bigBox = new Box(newMinCorner, newMaxCorner);

    return bigBox;
}

bool Box::intersect(Ray * ray) {
    float tmin = (minCorner.x - ray->getOrigin().x) / ray->getDirection().x;
    float tmax = (maxCorner.x - ray->getOrigin().x) / ray->getDirection().x;
 
    if (tmin > tmax) swap(tmin, tmax);
 
    float tymin = (minCorner.y - ray->getOrigin().y) / ray->getDirection().y;
    float tymax = (maxCorner.y - ray->getOrigin().y) / ray->getDirection().y;
 
    if (tymin > tymax) swap(tymin, tymax);
 
    if ((tmin > tymax) || (tymin > tmax))
        return false;
 
    if (tymin > tmin)
        tmin = tymin;
 
    if (tymax < tmax)
        tmax = tymax;
 
    float tzmin = (minCorner.z - ray->getOrigin().z) / ray->getDirection().z;
    float tzmax = (maxCorner.z - ray->getOrigin().z) / ray->getDirection().z;
 
    if (tzmin > tzmax) swap(tzmin, tzmax);
 
    if ((tmin > tzmax) || (tzmin > tmax))
        return false;
 
    if (tzmin > tmin)
        tmin = tzmin;
 
    if (tzmax < tmax)
        tmax = tzmax;
 
    return true;
}

vec3 Box::getMinCorner() {
    return minCorner;
}


vec3 Box::getMaxCorner() {
    return maxCorner;
}

bool Box::isEmpty() {
    return !(hasObj);
}
