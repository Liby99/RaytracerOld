#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Transform.h"
#include "Ray.h"

using namespace std;

typedef uint8_t BYTE;
typedef void (* renderProgressCallback)(int, int, vec3);

class Scene;

class Camera {
    private:
        
        // Final Static variables
        const static int COLOR_DIM = 3;
        const static int COLOR_R = 0;
        const static int COLOR_G = 1;
        const static int COLOR_B = 2;
        const static int BYTE_MAX = 255;
        
        // Reference to scene that the camera belongs to
        Scene * scene;
        
        // Basic Camera Variables
        vec3 pos;
        vec3 center;
        vec3 up;
        float fovy;
        
        // Basic setters for scene
        void setScene(Scene * scene);
    public:
        
        // Constructor
        Camera(Scene * scene, vec3 pos, vec3 center, vec3 up, float fovy);
        
        // Basic Setter
        void setPosition(vec3 pos);
        void setCenter(vec3 center);
        void setUp(vec3 up);
        void setFovy(float fovy);
        
        void rotate(float degree, vec3 axis);
        
        // Basic Getter
        vec3 getPosition();
        vec3 getCenter();
        vec3 getUp();
        float getFovy();
        
        // Get the rays that goes from this camera
        vector<Ray *> getRays();
        
        // Get the rendered image
        BYTE * getImage(renderProgressCallback callback);
};

#endif
