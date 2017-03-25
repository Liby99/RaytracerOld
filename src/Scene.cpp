#include "Scene.h"

using namespace std;

Scene::Scene() {
    setWidth(0);
    setHeight(0);
    setMaxDepth(DEFAULT_DEPTH);
    setDiffuse(vec3(0));
    setSpecular(vec3(0));
    setEmission(vec3(0));
    setAmbient(vec3(0.2));
    setAttenuation(vec3(1, 0, 0));
    initiateTransf();
}

Scene::~Scene() {
    clearCamera();
    clearLights();
    clearVertices();
    clearPrimitives();
    clearBoundingBox();
}

void Scene::setWidth(int width) {
    this->width = width;
}

void Scene::setHeight(int height) {
    this->height = height;
}

void Scene::setMaxDepth(int depth) {
    this->depth = depth;
}

void Scene::setDiffuse(vec3 diffuse) {
    this->diffuse = diffuse;
}

void Scene::setSpecular(vec3 specular) {
    this->specular = specular;
}

void Scene::setEmission(vec3 emission) {
    this->emission = emission;
}

void Scene::setAmbient(vec3 ambient) {
    this->ambient = ambient;
}

void Scene::setShininess(float shininess) {
    this->shininess = shininess;
}

void Scene::setAttenuation(vec3 attenuation) {
    this->attenuation = attenuation;
}

void Scene::setAttenuation(float c0, float c1, float c2) {
    this->setAttenuation(vec3(c0, c1, c2));
}

void Scene::onRenderProgress(renderProgressCallback func) {
    this->onRenderProgressCallback = func;
}

void Scene::updateTransf(mat4 m) {
    mat4 & t = transfStack.top();
    t = t * m;
}

mat4 Scene::peekTransf() {
    return transfStack.top();
}

void Scene::pushTransf() {
    transfStack.push(transfStack.top());
}

void Scene::popTransf() {
    if (transfStack.size() > 1) {
        transfStack.pop();
    }
    else {
        cout << "Cannot Pop From Transformation Stack" << endl;
    }
}

void Scene::createCamera(vec3 pos, vec3 center, vec3 up, float fovy) {
    setCamera(new Camera(this, pos, center, up, fovy));
}

void Scene::setCamera(Camera * camera) {
    this->camera = camera;
}

void Scene::rotateCamera(float degree, vec3 axis) {
    if (camera) {
        camera->rotate(degree, axis);
    }
}

void Scene::addLight(Light * light) {
    lights.push_back(light);
}

void Scene::addDirectionalLight(float x, float y, float z, float r, float g, float b) {
    vec3 direction = vec3(x, y, z);
    vec3 color = vec3(r, g, b);
    addLight(new DirectionalLight(direction, color));
}

void Scene::addPointLight(float x, float y, float z, float r, float g, float b) {
    vec3 position = vec3(x, y, z);
    vec3 color = vec3(r, g, b);
    addLight(new PointLight(position, color, attenuation));
}

void Scene::addVertex(Vertex * vertex) {
    vertices.push_back(vertex);
}

void Scene::addVertex(float x, float y, float z) {
    addVertex(new Vertex(x, y, z));
}

void Scene::addVertex(float x, float y, float z, float nx, float ny, float nz) {
    addVertex(new Vertex(x, y, z, nx, ny, nz));
}

void Scene::addPrimitive(Primitive * primitive) {
    primitives.push_back(primitive);
}

void Scene::addTriangle(Triangle * triangle) {
    addPrimitive((Primitive *) triangle);
}

void Scene::addTriangle(Vertex * v1, Vertex * v2, Vertex * v3) {
    addTriangle(new Triangle(this, peekTransf(), v1, v2, v3, diffuse, specular, emission, ambient, shininess));
}

void Scene::addTriangle(int i1, int i2, int i3) {
    addTriangle(vertices[i1], vertices[i2], vertices[i3]);
}

void Scene::addCube(Cube * cube) {
    addPrimitive((Primitive *) cube);
}

void Scene::addCube(vec3 center, float side) {
    addCube(new Cube(this, peekTransf(), center, side, diffuse, specular, emission, ambient, shininess));
}

void Scene::addCube(float x, float y, float z, float side) {
    addCube(vec3(x, y, z), side);
}

void Scene::addSphere(Sphere * sphere) {
    addPrimitive((Primitive *) sphere);
}

void Scene::addSphere(vec3 center, float radius) {
    addSphere(new Sphere(this, peekTransf(), center, radius, diffuse, specular, emission, ambient, shininess));
}

void Scene::addSphere(float x, float y, float z, float radius) {
    addSphere(vec3(x, y, z), radius);
}

int Scene::getWidth() {
    return width;
}

int Scene::getHeight() {
    return height;
}

int Scene::getMaxDepth() {
    return depth;
}

Camera * Scene::getCamera() {
    return camera;
}

vector<Light *> Scene::getLights() {
    return lights;
}

vector<Primitive *> Scene::getPrimitives() {
    return primitives;
}

vector<Vertex *> Scene::getVertices() {
    return vertices;
}

Bvh * Scene::getBvh() {
    return bvh;
}

void Scene::constructBoundingBox() {
    bvh = new Bvh(primitives);
}

void Scene::clearBoundingBox() {
    if (bvh) {
        delete bvh;
    }
}

BYTE * Scene::render() {
    if (camera) {
        
        cout << "Attempting to build tree" << endl;
        constructBoundingBox();
        cout << "Tree Built!" << endl;
        
        // First get the rays that goes from the camera
        vector<Ray *> rays = camera->getRays();
        BYTE * image = new BYTE[width * height * COLOR_DIM];
        
        for (int i = 0; i < rays.size(); i++) {
            
            // Get the color from the ray
            vec3 color = rays[i]->getColor();
            
            // Fill the color into the byte array
            image[COLOR_DIM * i + COLOR_B] = BYTE_MAX * color.x;
            image[COLOR_DIM * i + COLOR_G] = BYTE_MAX * color.y;
            image[COLOR_DIM * i + COLOR_R] = BYTE_MAX * color.z;
            
            (*onRenderProgressCallback)(i, rays.size(), color);
            
            // Remove the ray since we will no longer need it.
            delete rays[i];
        }
        
        return image;
    }
    else {
        return nullptr;
    }
}

void Scene::initiateTransf() {
    transfStack = stack<mat4>();
    transfStack.push(mat4(1.0));
}

void Scene::clearCamera() {
    if (this->camera) {
        delete this->camera;
    }
}

void Scene::clearLights() {
    for (int i = 0; i < lights.size(); i++) {
        delete lights[i];
    }
}

void Scene::clearPrimitives() {
    for (int i = 0; i < primitives.size(); i++) {
        delete primitives[i];
    }
}

void Scene::clearVertices() {
    for (int i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
}
