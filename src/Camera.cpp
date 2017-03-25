#include "Camera.h"
#include "Scene.h"

Camera::Camera(Scene * scene, vec3 pos, vec3 center, vec3 up, float fovy) {
    setScene(scene);
    setPosition(pos);
    setCenter(center);
    setUp(up);
    setFovy(fovy);
}

void Camera::setScene(Scene * scene) {
    this->scene = scene;
}

void Camera::setPosition(vec3 pos) {
    this->pos = pos;
}

void Camera::setCenter(vec3 center) {
    this->center = center;
}

void Camera::setUp(vec3 up) {
    this->up = up;
}

void Camera::setFovy(float fovy) {
    this->fovy = fovy;
}

void Camera::rotate(float degree, vec3 axis) {
    mat3 matrix = Transform::rotate(degree, axis);
    vec3 position = getPosition();
    position -= getCenter();
    position = matrix * position;
    setPosition(position);
}

vec3 Camera::getPosition() {
    return this->pos;
}

vec3 Camera::getCenter() {
    return this->center;
}

vec3 Camera::getUp() {
    return this->up;
}

vector<Ray *> Camera::getRays() {
    
    // Basic camera variables
    int width = scene->getWidth();
    int height = scene->getHeight();
    vec3 w = normalize(pos - center);
    vec3 u = normalize(cross(w, up));
    vec3 v = cross(w, u);
    
    // Cached uniform variables
    float betaMult = -tan(glm::radians(fovy / 2));
    float alphaMult = betaMult * width / height;
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    
    // Initiate Rays Vector
    vector<Ray *> rays = vector<Ray *>();
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            
            // First get the ni and nj
            float ni = i + 0.5;
            float nj = j + 0.5;
            
            // Then calculate alpha and beta then direction of ray
            float alpha = alphaMult * (ni - halfWidth) / halfWidth;
            float beta = betaMult * (nj - halfHeight) / halfHeight;
            vec3 dir = normalize(alpha * u + beta * v - w);
            
            // Finally store the ray object
            rays.push_back(new Ray(scene, pos, dir));
        }
    }
    
    return rays;
}

BYTE * Camera::getImage(renderProgressCallback callback) {
    
    int width = scene->getWidth();
    int height = scene->getHeight();
    
    // First get the rays that goes from the camera
    vector<Ray *> rays = getRays();
    BYTE * image = new BYTE[width * height * COLOR_DIM];
    
    for (int i = 0; i < rays.size(); i++) {
        
        // Get the color from the ray
        vec3 color = rays[i]->getColor();
        
        // Fill the color into the byte array
        image[COLOR_DIM * i + COLOR_B] = BYTE_MAX * color.x;
        image[COLOR_DIM * i + COLOR_G] = BYTE_MAX * color.y;
        image[COLOR_DIM * i + COLOR_R] = BYTE_MAX * color.z;
        
        (*callback)(i, rays.size(), color);
        
        // Remove the ray since we will no longer need it.
        delete rays[i];
    }
    
    return image;
}
