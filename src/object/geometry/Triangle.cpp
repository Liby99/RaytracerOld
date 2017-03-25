#include "Triangle.h"
#include "Box.h"

Triangle::Triangle(Scene * scene, mat4 transform, Vertex * v1, Vertex * v2, Vertex * v3, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shinness) :
    Primitive(scene, transform, diffuse, specular, emission, ambient, shinness),
    v1(v1),
    v2(v2),
    v3(v3) {

    // Check whether the triangle need interpolation
    this->needInterpolate = v1->hasNormal() && v2->hasNormal() && v3->hasNormal();
}

vec3 Triangle::interpolateNormal(vec3 position) {

    // First get the bary centric coordinate for the position
    vec3 lambda = getBaryCentric(position);

    // Finally Get the Normal using the linear combination of three normals
    vec3 normal = lambda.x * v1->getNormal() +
                  lambda.y * v2->getNormal() +
                  lambda.z * v3->getNormal();

    // Finally Normalize the normal
    return normalize(normal);
}

vec3 Triangle::getBaryCentric(vec3 position) {
    vec3 result = vec3(0, 0, 0);
    vec3 p1 = v1->getPosition();
    vec3 p2 = v2->getPosition();
    vec3 p3 = v3->getPosition();
    vec3 t0 = p2 - p1, t1 = p3 - p1, t2 = position - p1;
    float d00 = dot(t0, t0);
    float d01 = dot(t0, t1);
    float d11 = dot(t1, t1);
    float d20 = dot(t2, t0);
    float d21 = dot(t2, t1);
    float denom = d00 * d11 - d01 * d01;
    result.x = (d11 * d20 - d01 * d21) / denom;
    result.y = (d00 * d21 - d01 * d20) / denom;
    result.z = 1.0f - result.x - result.y;
    return result;
}

Intersection * Triangle::intersect(Ray * ray) {

    // Pre cache the positions
    vec3 p1 = v1->getPosition();
    vec3 p2 = v2->getPosition();
    vec3 p3 = v3->getPosition();
    mat4 inverseTransf = inverse(transform);

    // Same the intersection result
    Intersection * intersection = new Intersection(scene, ray, this);

    // Same the variables
    vec4 _o = inverseTransf * vec4(ray->getOrigin(), 1);
    vec3 origin = vec3(_o) / _o.w;
    vec3 direction = vec3(inverseTransf * vec4(ray->getDirection(), 0));
    vec3 normal = -cross(p2 - p1, p3 - p1);

    // If the triangle is in a straight line, then intersection not exist
    if (normal.x == 0 && normal.y == 0 && normal.z == 0) {
        return intersection;
    }

    normal = normalize(normal);

    // Calculate t
    float t = (dot(p1, normal) - dot(origin, normal)) / dot(direction, normal);

    // Pre cache the position of the intersection
    vec3 position = origin + t * direction;
    vec3 lambda = getBaryCentric(position);

    // Check if t is greater then 0 and the position is inside the triangle
    if (t > 0 &&
        lambda.x >= 0 && lambda.x <= 1 &&
        lambda.y >= 0 && lambda.y <= 1 &&
        lambda.z >= 0 && lambda.z <= 1) {

        // Then set the intersection to hit
        intersection->setHit(true);
        intersection->setT(t);
        intersection->setIntersect(position);
        intersection->setNormal(needInterpolate ? interpolateNormal(position) : -normal);
        intersection->applyTransformation(transform);
    }

    // Return the intersection
    return intersection;
}

/*
 * This function returns a vector of three vectices' positions
 */
vector<vec3> Triangle::getVertices() {
    vector<vec3> vertices;
    vec4 _v1 = transform * vec4(v1->getPosition(), 1);
    vec4 _v2 = transform * vec4(v2->getPosition(), 1);
    vec4 _v3 = transform * vec4(v3->getPosition(), 1);
    vertices.push_back(vec3(_v1) / _v1.w);
    vertices.push_back(vec3(_v2) / _v2.w);
    vertices.push_back(vec3(_v3) / _v3.w);
    return vertices;
}

bool Triangle::intersectBox(vec3 minCorner, vec3 maxCorner) {
    Box box = Box(this);
    vec3 priMin = box.getMinCorner();
    vec3 priMax = box.getMaxCorner();
    float x = min(maxCorner.x, priMax.x) - max(minCorner.x, priMin.x);
    float y = min(maxCorner.y, priMax.y) - max(minCorner.y, priMin.y);
    float z = min(maxCorner.z, priMax.z) - max(minCorner.z, priMin.z);
    return x >= 0 && y >= 0 && z >= 0;
}

vec3 Triangle::getCenter() {
    vec3 center = ((v1->getPosition() + v2->getPosition() + v3->getPosition()) / 3.0f);
    vec4 _center = transform * vec4(center, 1);
    return vec3(_center) / _center.w;
}
