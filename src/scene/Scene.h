#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <stack>

#include "Transform.h"
#include "Camera.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Vertex.h"
#include "Primitive.h"
#include "Triangle.h"
#include "Cube.h"
#include "Sphere.h"
#include "Bvh.h"
#include "BvhNode.h"
#include "Box.h"

using namespace std;

typedef uint8_t BYTE;
typedef void (* renderProgressCallback)(int, int, vec3);

class Scene {
    private:
        
        // Final Static variables
        const static int COLOR_DIM = 3;
        const static int COLOR_R = 0;
        const static int COLOR_G = 1;
        const static int COLOR_B = 2;
        const static int BYTE_MAX = 255;
        
        const static int DEFAULT_DEPTH = 5;
        
        renderProgressCallback onRenderProgressCallback;
        
        Bvh * bvh;
        
        // Dimension of the Scene
        int width;
        int height;
        int depth;
        
        // Scene Contents
        Camera * camera;
        vector<Light *> lights;
        vector<Primitive *> primitives;
        vector<Vertex *> vertices;
        
        // Stack of transformation
        stack<mat4> transfStack;
        
        // Scene Lighting Configuration
        vec3 diffuse;
        vec3 specular;
        vec3 emission;
        vec3 ambient;
        float shininess;
        
        vec3 attenuation;
        
        // Helper Methods
        void initiateTransf();
        void clearCamera();
        void clearLights();
        void clearPrimitives();
        void clearVertices();
        
        // Acceleration Structure
        void constructBoundingBox();
        void clearBoundingBox();
    public:
        
        // Constructor & Destructor
        Scene();
        ~Scene();
        
        // Basic Getter
        int getWidth();
        int getHeight();
        int getMaxDepth();
        Camera * getCamera();
        vector<Light *> getLights();
        vector<Primitive *> getPrimitives();
        vector<Vertex *> getVertices();
        Bvh * getBvh();
        
        // Scene Dimension Setters
        void setWidth(int width);
        void setHeight(int height);
        void setMaxDepth(int depth);
        
        // Scene Color Setters
        void setDiffuse(vec3 diffuse);
        void setSpecular(vec3 specular);
        void setEmission(vec3 emission);
        void setAmbient(vec3 ambient);
        void setShininess(float shininess);
        
        // Scene attenuation for lights
        void setAttenuation(vec3 attenuation);
        void setAttenuation(float c0, float c1, float c2);
        
        // Event Listener
        void onRenderProgress(renderProgressCallback func);
        
        // Transformation Setters
        void updateTransf(mat4 matrix);
        mat4 peekTransf();
        void pushTransf();
        void popTransf();
        
        // Create and Set Camera
        void createCamera(vec3 pos, vec3 center, vec3 up, float fovy);
        void setCamera(Camera * camera);
        void rotateCamera(float degree, vec3 axis);
        
        // Add Light
        void addLight(Light * light);
        void addDirectionalLight(float x, float y, float z, float r, float g, float b);
        void addPointLight(float x, float y, float z, float r, float g, float b);
        
        // Add Vertex
        void addVertex(Vertex * vertex);
        void addVertex(float x, float y, float z);
        void addVertex(float x, float y, float z, float nx, float ny, float nz);
        
        // Add Primitive
        void addPrimitive(Primitive * primitive);
        
        // Add Triangle
        void addTriangle(Triangle * triangle);
        void addTriangle(Vertex * v1, Vertex * v2, Vertex * v3);
        void addTriangle(int i1, int i2, int i3);
        
        // Add Cube
        void addCube(Cube * cube);
        void addCube(vec3 center, float side);
        void addCube(float x, float y, float z, float side);
        
        // Add Sphere
        void addSphere(Sphere * sphere);
        void addSphere(vec3 center, float radius);
        void addSphere(float x, float y, float z, float radius);
        
        // Render the image from the camera
        BYTE * render();
};

#endif
