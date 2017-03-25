#ifndef VERTEX_H
#define VERTEX_H

#include "Transform.h"

using namespace std;

class Vertex {
    private:
        vec3 position;
        vec3 normal;
        bool hasNormalFlag;
    public:
        Vertex(float x, float y, float z);
        Vertex(float x, float y, float z, float nx, float ny, float nz);
        bool hasNormal();
        vec3 getPosition();
        vec3 getNormal();
};

#endif
