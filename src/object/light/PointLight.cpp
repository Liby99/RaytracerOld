#include "PointLight.cpp"

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
