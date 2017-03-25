#include "Intersection.h"
#include "Scene.h"
#include "Primitive.h"

float max(float f1, float f2) {
    return f1 > f2 ? f1 : f2;
}

const float Intersection::INCREMENT = 0.001;

Intersection::Intersection(Scene * scene, Ray * ray, Primitive * object) {
    setScene(scene);
    setRay(ray);
    setObject(object);
    setHit(false);
    setT(0);
}

void Intersection::setHit(bool hitFlag) {
    this->hitFlag = hitFlag;
}

void Intersection::setT(float t) {
    if (t < 0) {
        this->hitFlag = false;
        this->t = 0;
        return;
    }
    this->t = t;
}

void Intersection::setIntersect(vec3 intersect) {
    this->intersect = intersect;
}

void Intersection::setNormal(vec3 normal) {
    this->normal = normalize(normal);
}

bool Intersection::hit() {
    return this->hitFlag;
}

vec3 Intersection::getIntersect() {
    return this->intersect;
}

vec3 Intersection::getNormal() {
    return this->normal;
}

void Intersection::applyTransformation(mat4 transform) {
    vec4 nPos = transform * vec4(intersect, 1);
    vec4 nNorm = transpose(inverse(transform)) * vec4(normal, 0);
    setIntersect(vec3(nPos) / nPos.w);
    setNormal(vec3(nNorm));
}

Primitive * Intersection::getObject() {
    return this->object;
}

float Intersection::getDistanceToOrigin() {
    vec3 diff = intersect - ray->getOrigin();
    return sqrt(dot(diff, diff));
}

vec3 Intersection::getColor() {
    vec3 color = vec3(0, 0, 0);
    color += object->getAmbient();
    color += object->getEmission();
    color += getLightingColor();
    color += getReflectingColor();
    for (int i = 0; i < 3; i++) {
        color[i] = color[i] > 1 ? 1 : color[i];
    }
    return color;
}

vec3 Intersection::getLightingColorHelper(vec3 lightness, vec3 diffuse, vec3 normal, vec3 direction, vec3 specular, vec3 halfAngle, float shininess) {
    vec3 lambert = diffuse * max(dot(normal, direction), 0.0);
    vec3 blinn = specular * pow(max(dot(normal, halfAngle), 0.0), shininess);
    return lightness * (lambert + blinn);
}

vec3 Intersection::getPointLightingColor(PointLight * pLight) {
    
    // Prepare the basic parameters for point light
    vec3 intersect = getIntersect();
    vec3 lightPos = pLight->getPosition();
    vec3 diff = lightPos - intersect;
    Ray toLight = Ray(scene, intersect + INCREMENT * diff, diff);
    vec3 lightColor = pLight->getColor();
    float dist = sqrt(dot(diff, diff));
    bool hasShadow = false;
    
    // Check if there's object intercepting light
    vector<Intersection *> intersections = toLight.getIntersections();
    for (int i = 0; i < intersections.size(); i++) {
        if (intersections[i]->getDistanceToOrigin() < dist) {
            hasShadow = true;
        }
        delete intersections[i];
    }
    
    if (!hasShadow) {
        // Calculate the lightness with attenuation
        vec3 atten = pLight->getAttenuation();
        lightColor = lightColor / (atten.x + atten.y * dist + atten.z * dist * dist);
        
        // Calculate the halfangle and calculate the final color
        vec3 halfAngle = normalize(toLight.getDirection() - ray->getDirection());
        vec3 color = getLightingColorHelper(lightColor, object->getDiffuse(), getNormal(), toLight.getDirection(), object->getSpecular(), halfAngle, object->getShininess());
        
        return color;
    }
    else {
        return vec3(0, 0, 0);
    }
}

vec3 Intersection::getDirectionalLightingColor(DirectionalLight * dLight) {
    
    // Prepare the basic parameters for directional light
    vec3 intersect = getIntersect();
    vec3 direction = dLight->getDirection();
    Ray toLight = Ray(scene, intersect + INCREMENT * direction, direction);
    
    // Check if there's object on the direction
    if (!toLight.hasIntersection()) {
        vec3 halfAngle = normalize(direction - ray->getDirection());
        return getLightingColorHelper(dLight->getColor(), object->getDiffuse(), getNormal(), toLight.getDirection(), object->getSpecular(), halfAngle, object->getShininess());
    }
    else {
        return vec3(0, 0, 0);
    }
}

vec3 Intersection::getLightingColor() {
    vec3 color = vec3(0, 0, 0);
    for (int i = 0; i < scene->getLights().size(); i++) {
        
        // Check if the light is point light or directional light
        Light * light = scene->getLights()[i];
        if (light->getType() == Light::POINT_LIGHT) {
            color += getPointLightingColor(static_cast<PointLight *>(light));
        }
        else if (light->getType() == Light::DIRECTIONAL_LIGHT) {
            color += getDirectionalLightingColor(static_cast<DirectionalLight *>(light));
        }
    }
    return color;
}

vec3 Intersection::getReflectingColor() {
    vec3 color = vec3(0, 0, 0);
    if (object->getSpecular() != vec3(0, 0, 0)) {
        
        // First calculate the reflection ray
        vec3 origin = getIntersect();
        vec3 direction = ray->getDirection() - vec3(2.0 * dot(ray->getDirection(), getNormal())) * getNormal();
        Ray reflection = Ray(scene, origin + INCREMENT * direction, direction, ray->getDepth() + 1);
        
        // Then construct and return the color
        color = object->getSpecular() * reflection.getColor();
    }
    return color;
}

void Intersection::setScene(Scene * scene) {
    this->scene = scene;
}

void Intersection::setRay(Ray * ray) {
    this->ray = ray;
}

void Intersection::setObject(Primitive * object) {
    this->object = object;
}
