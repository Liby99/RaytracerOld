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

PointLight::PointLight(vec3 position, vec3 color, vec3 attenuation) :
    Light(color) {
    this->position = position;
    this->attenuation = attenuation;
    this->type = POINT_LIGHT;
}

vec3 PointLight::getPosition() {
    return this->position;
}

vec3 PointLight::getAttenuation() {
    return this->attenuation;
}

DirectionalLight::DirectionalLight(vec3 direction, vec3 color) :
    Light(color) {
    this->direction = normalize(direction);
    this->type = DIRECTIONAL_LIGHT;
}

vec3 DirectionalLight::getDirection() {
    return this->direction;
}
