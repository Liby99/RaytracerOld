#ifndef BVH_H
#define BVH_H

#include "Box.h"
#include "BvhNode.h"

class Bvh {
    private:
        BvhNode * root;
    public:
        Bvh(std::vector<Primitive *> & objs);
        ~Bvh();
        BvhNode * getRoot();
};

#endif
