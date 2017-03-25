#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"

Ray::Ray(Scene * scene, vec3 origin, vec3 direction) {
    setScene(scene);
    setOrigin(origin);
    setDirection(normalize(direction));
    setDepth(0);
}

Ray::Ray(Scene * scene, vec3 origin, vec3 direction, int depth) {
    setScene(scene);
    setOrigin(origin);
    setDirection(normalize(direction));
    setDepth(depth);
}

int Ray::getDepth() {
    return this->depth;
}

void Ray::setDepth(int depth) {
    this->depth = depth;
}

vec3 Ray::getOrigin() {
    return origin;
}

vec3 Ray::getDirection() {
    return direction;
}

void Ray::setScene(Scene * scene) {
    this->scene = scene;
}

void Ray::setOrigin(vec3 origin) {
    this->origin = origin;
}

void Ray::setDirection(vec3 direction) {
    this->direction = normalize(direction);
}

bool Ray::hasIntersectionHelper(BvhNode * node) {
    
    // Return if not intersecting with the box in the node
    if (node == nullptr || !node->getBox()->intersect(this)) {
        return false;
    }
    
    if (node->isLeaf()) {
        for (int i = 0; i < node->getObjects().size(); i++) {
            Intersection * intersect = node->getObjects()[i]->intersect(this);
            if (intersect->hit()) {
                return true;
            }
        }
        return false;
    }
    else {
        return hasIntersectionHelper(node->getLeft()) || hasIntersectionHelper(node->getRight());
    }
}

bool Ray::hasIntersection() {
    return hasIntersectionHelper(scene->getBvh()->getRoot());
}

void Ray::getIntersectionsHelper(BvhNode * node, vector<Intersection *> & intersections) {
    
    // Return if not intersecting with the box in the node
    if (node == nullptr || !node->getBox()->intersect(this)) {
        return;
    }
    
    if (node->isLeaf()) {
        for (int i = 0; i < node->getObjects().size(); i++) {
            Intersection * intersect = node->getObjects()[i]->intersect(this);
            if (intersect->hit()) {
                intersections.push_back(intersect);
            }
        }
    }
    else {
        getIntersectionsHelper(node->getLeft(), intersections);
        getIntersectionsHelper(node->getRight(), intersections);
    }
}

vector<Intersection *> Ray::getIntersections() {
    vector<Intersection *> intersections;
    
    // Used Acceleration Structure
    getIntersectionsHelper(scene->getBvh()->getRoot(), intersections);
    
    // Old Approach
    // for (int i = 0; i < scene->getPrimitives().size(); i++) {
    //     Primitive * object = scene->getPrimitives()[i];
    //     Intersection * intersection = object->intersect(this);
    //     if (intersection->hit()) {
    //         intersections.push_back(intersection);
    //     }
    // }
    
    return intersections;
}

vec3 Ray::getColor() {
    vec3 color;
    if (depth < scene->getMaxDepth()) {
        vector<Intersection *> intersections = getIntersections();
        if (intersections.size() == 0) {
            color = vec3(0, 0, 0);
        }
        else {
            float minDist;
            Intersection * minIntersect;
            for (int i = 0; i < intersections.size(); i++) {
                vec3 diff = intersections[i]->getIntersect() - getOrigin();
                float dist = dot(diff, diff);
                if (i == 0 || dist < minDist) {
                    minDist = dist;
                    minIntersect = intersections[i];
                }
            }
            color = minIntersect->getColor();
            for (int i = 0; i < intersections.size(); i++) {
                delete intersections[i];
            }
        }
    }
    else {
        color = vec3(0, 0, 0);
    }
    return color;
}
