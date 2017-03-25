#include "Primitive.h"
#include "Box.h"

void printVec3(vec3 v) {
    cout << "(" << v.x << "," << v.y << "," << v.z << ")" << endl;
}

void printMatrix3(mat3 m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

void printMatrix2(mat2 m) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

Primitive::Primitive(Scene * scene, mat4 transform, vec3 diffuse, vec3 specular, vec3 emission, vec3 ambient, float shininess) {

    // Set up the scene the primitive belongs to
    this->scene = scene;

    // Set up the transformation matrix
    this->transform = transform;

    // Set up the color properties of the primitive
    this->diffuse = diffuse;
    this->specular = specular;
    this->emission = emission;
    this->ambient = ambient;
    this->shininess = shininess;
}

Intersection * Primitive::intersect(Ray * ray) {
    return new Intersection(scene, ray, this);
}

vec3 Primitive::getDiffuse() {
    return diffuse;
}

vec3 Primitive::getSpecular() {
    return specular;
}

vec3 Primitive::getEmission() {
    return emission;
}

vec3 Primitive::getAmbient() {
    return ambient;
}

float Primitive::getShininess() {
    return shininess;
}

vector<vec3> Primitive::getVertices() {
  return vector<vec3>();
}

vec3 Primitive::getCenter() {
  return vec3();
}

bool Primitive::intersectBox(vec3 minCorner, vec3 maxCorner) {
    return false;
}
