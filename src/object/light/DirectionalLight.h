#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

using namespace std;

class DirectionalLight : public Light {
    private:
        vec3 direction;
    public:
        DirectionalLight(vec3 direction, vec3 color);
        vec3 getDirection();
};

#endif
