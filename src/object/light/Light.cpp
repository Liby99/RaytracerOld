#include "Light.h"

Light::Light(vec3 color) {
    this->color = color;
    this->type = LIGHT;
}

vec3 Light::getColor() {
    return this->color;
}

int Light::getType() {
    return this->type;
}
