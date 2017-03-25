#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 direction, vec3 color) :
    Light(color) {
    this->direction = normalize(direction);
    this->type = DIRECTIONAL_LIGHT;
}

vec3 DirectionalLight::getDirection() {
    return this->direction;
}
