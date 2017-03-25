#include "Cube.h"

Cube::Cube(Scene * scene, mat4 transform, vec3 center, float side, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shininess) :
    Primitive(scene, transform, diffuse, specular, emission, ambient, shininess) {
    
    // Store the cube properties
    this->center = center;
    this->side = side;
}

Intersection * Cube::intersect(Ray * ray) {
    
    /* TODO */
    return new Intersection(scene, ray, this);
}
