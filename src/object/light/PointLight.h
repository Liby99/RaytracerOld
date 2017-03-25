#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

using namespace std;

class PointLight : public Light {
    private:
        vec3 position;
        vec3 attenuation;
    public:
        PointLight(vec3 position, vec3 color, vec3 attenuation);
        vec3 getPosition();
        vec3 getAttenuation();
};

#endif
