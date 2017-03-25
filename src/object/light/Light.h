#ifndef LIGHT_H
#define LIGHT_H

#include "Transform.h"

using namespace std;

class Light {
    private:
        vec3 color;
    protected:
        int type;
    public:
        
        // Type Constants
        const static int LIGHT = 0;
        const static int POINT_LIGHT = 1;
        const static int DIRECTIONAL_LIGHT = 2;
        
        //
        Light(vec3 color);
        virtual vec3 getColor();
        virtual int getType();
};

#endif
