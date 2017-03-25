#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) {
    this->hasNormalFlag = false;
    this->position = vec3(x, y, z);
}

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz) {
    this->hasNormalFlag = true;
    this->position = vec3(x, y, z);
    this->normal = vec3(nx, ny, nz);
}

bool Vertex::hasNormal() {
    return this->hasNormalFlag;
}

vec3 Vertex::getPosition() {
    return this->position;
}

vec3 Vertex::getNormal() {
    return this->normal;
}
