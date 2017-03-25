#include "Bvh.h"

using namespace std;

void removeBvhNode(BvhNode * node) {
    if (node->getLeft()) {
        removeBvhNode(node->getLeft());
    }
    if (node->getRight()) {
        removeBvhNode(node->getRight());
    }
    delete node;
}

Bvh::Bvh(vector<Primitive *> & objs) {
    root = new BvhNode();
    root->create(objs, 0);
}

Bvh::~Bvh() {
    if (root) {
        removeBvhNode(root);
    }
}

BvhNode * Bvh::getRoot() {
    return root;
}
