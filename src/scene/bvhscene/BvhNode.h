#ifndef BVHNODE_H
#define BVHNODE_H

#include "Box.h"

class BvhNode {
    private:
        BvhNode * left;
        BvhNode * right;
        Box * bbox;
        vector<Primitive *> primitives;
        bool isLeafFlag;

    public:
        BvhNode();
        BvhNode(Primitive* obj);
        ~BvhNode();

        void create(std::vector<Primitive*> & objs, int axis);

        BvhNode * getLeft();
        BvhNode * getRight();
        Box * getBox();
        bool isLeaf();
        vector<Primitive *> getObjects();
};

#endif
