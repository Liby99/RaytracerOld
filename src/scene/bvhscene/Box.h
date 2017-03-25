#ifndef BOX_H
#define BOX_H

#include "Transform.h"
#include "Primitive.h"

class Box {
    private:
        vec3 minCorner;
        vec3 maxCorner;
        bool hasObj;

        void extend(Primitive * obj);

    public:
        Box();
        Box(Primitive * obj);
        Box(vector<Primitive *> & objs);
        Box(vec3 minCorner, vec3 maxCorner);

        Box* combine(Box * box1, Box * box2);
        bool intersect(Ray * ray);

        vec3 getMinCorner();
        vec3 getMaxCorner();
        bool isEmpty();
};

#endif
