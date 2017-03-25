#include "Sphere.h"
#include "Box.h"

Sphere::Sphere(Scene * scene, mat4 transform, vec3 center, float radius, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shininess) :
    Primitive(scene, transform, diffuse, specular, emission, ambient, shininess) {

    // Store the sphere properties
    this->center = center;
    this->radius = radius;
}

Intersection * Sphere::intersect(Ray * ray) {

    mat4 inverseTransf = inverse(transform);

    vec4 _p0 = inverseTransf * vec4(ray->getOrigin(), 1);
    vec3 p0 = vec3(_p0) / _p0.w;
    vec3 p1 = normalize(vec3(inverseTransf * vec4(ray->getDirection(), 0)));
    vec3 org = this->center;
    float r = this->radius;

    float t;
    bool hit = false;
    float a = dot(p1, p1);
    float b = 2.0f * dot(p1, p0 - org);
    float c = dot(p0 - org, p0 - org) - r * r;
    float t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    float t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

    if (t1 > 0 && t2 > 0) {
        hit = true;
        t = min(t1, t2);
    }
    else if (t1 * t2 < 0) {
        hit = true;
        t = max(t1, t2);
    }

    Intersection * retIntersection = new Intersection(scene, ray, this);

    if (hit) {
        retIntersection->setHit(true);
        retIntersection->setT(t);
        retIntersection->setIntersect(p0 + t * p1);
        retIntersection->setNormal(normalize(p0 + t * p1 - org));
        retIntersection->applyTransformation(transform);
    }

    return retIntersection;
}



vector<vec3> Sphere::getVertices() {
    vector<vec3> vertices;
    vec4 _v1 = transform * vec4(center.x - radius, center.y - radius, center.z - radius, 1);
    vec4 _v2 = transform * vec4(center.x - radius, center.y - radius, center.z + radius, 1);
    vec4 _v3 = transform * vec4(center.x - radius, center.y + radius, center.z - radius, 1);
    vec4 _v4 = transform * vec4(center.x - radius, center.y + radius, center.z + radius, 1);
    vec4 _v5 = transform * vec4(center.x + radius, center.y - radius, center.z - radius, 1);
    vec4 _v6 = transform * vec4(center.x + radius, center.y - radius, center.z + radius, 1);
    vec4 _v7 = transform * vec4(center.x + radius, center.y + radius, center.z - radius, 1);
    vec4 _v8 = transform * vec4(center.x + radius, center.y + radius, center.z + radius, 1);
    vertices.push_back(vec3(_v1) / _v1.w);
    vertices.push_back(vec3(_v2) / _v2.w);
    vertices.push_back(vec3(_v3) / _v3.w);
    vertices.push_back(vec3(_v4) / _v4.w);
    vertices.push_back(vec3(_v5) / _v5.w);
    vertices.push_back(vec3(_v6) / _v6.w);
    vertices.push_back(vec3(_v7) / _v7.w);
    vertices.push_back(vec3(_v8) / _v8.w);
    return vertices;
}

bool Sphere::intersectBox(vec3 minCorner, vec3 maxCorner) {
    Box box = Box(this);
    vec3 priMin = box.getMinCorner();
    vec3 priMax = box.getMaxCorner();
    float x = min(maxCorner.x, priMax.x) - max(minCorner.x, priMin.x);
    float y = min(maxCorner.y, priMax.y) - max(minCorner.y, priMin.y);
    float z = min(maxCorner.z, priMax.z) - max(minCorner.z, priMin.z);
    return x >= 0 && y >= 0 && z >= 0;
}

vec3 Sphere::getCenter() {
    // vec4 _center = transform * vec4(center, 1);
    // return vec3(_center) / _center.w;
    return center;
}
