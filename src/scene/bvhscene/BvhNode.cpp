#include "BvhNode.h"

using namespace std;

BvhNode::BvhNode() {
    left = NULL;
    right = NULL;
    bbox = NULL;
}

BvhNode::BvhNode(Primitive * obj) {
    left = NULL;
    right = NULL;
    isLeafFlag = true;
    bbox = new Box(obj);
    primitives.push_back(obj);
}

BvhNode::~BvhNode() {
    delete bbox;
}

/*
 * axis 0 = x-axis; 1 = y-axis; 2 = z-axis
 */
void BvhNode::create(vector<Primitive *> &objs, int axis) {
    int n = objs.size();
    bbox = new Box(objs);
    
    vec3 mic = bbox->getMinCorner();
    vec3 mac = bbox->getMaxCorner();
    
    cout << "creating bvhnode. objs size " << n << endl;
    
    if (n == 0) {
        isLeafFlag = false;
        return;
    }
    else if (n == 1) {
        isLeafFlag = true;
        primitives.push_back(objs[0]);
    }
    else if (n == 2) {
        isLeafFlag = false;
        left = new BvhNode(objs[0]);
        right = new BvhNode(objs[1]);
    }
    else {
        vector<Primitive *> leftObjs = vector<Primitive *>();
        vector<Primitive *> rightObjs = vector<Primitive *>();
        float m;
        switch (axis) {
            case 0:
                m = (bbox->getMaxCorner().x + bbox->getMinCorner().x) / 2;
                for (int i = 0; i < n; i++) {
                    if (objs[i]->intersectBox(mic, vec3(m, mac.y, mac.z))) {
                        leftObjs.push_back(objs[i]);
                    }
                    if (objs[i]->intersectBox(vec3(m, mic.y, mic.z), mac)) {
                        rightObjs.push_back(objs[i]);
                    }
                }
                break;
            case 1:
                m = (bbox->getMaxCorner().y + bbox->getMinCorner().y) / 2;
                for (int i = 0; i < n; i++) {
                    if (objs[i]->intersectBox(mic, vec3(mac.x, m, mac.z))) {
                        leftObjs.push_back(objs[i]);
                    }
                    if (objs[i]->intersectBox(vec3(mic.x, m, mic.z), mac)) {
                        rightObjs.push_back(objs[i]);
                    }
                }
                break;
            case 2:
                m = (bbox->getMaxCorner().z + bbox->getMinCorner().z) / 2;
                for (int i = 0; i < n; i++) {
                    if (objs[i]->intersectBox(mic, vec3(mac.x, mac.y, m))) {
                        leftObjs.push_back(objs[i]);
                    }
                    if (objs[i]->intersectBox(vec3(mic.x, mic.y, m), mac)) {
                        rightObjs.push_back(objs[i]);
                    }
                }
                break;
        }
        
        cout << "left size: " << leftObjs.size() << endl;
        cout << "right size: " << rightObjs.size() << endl;
        
        if (leftObjs.size() == objs.size() || rightObjs.size() == objs.size()) {
            primitives = objs;
            isLeafFlag = true;
        }
        else {
            left = new BvhNode();
            left->create(leftObjs, (axis + 1) % 3);
            right = new BvhNode();
            right->create(rightObjs, (axis + 1) % 3);
            bbox = bbox->combine(left->getBox(), right->getBox());
            isLeafFlag = false;
        }
    }
}

BvhNode * BvhNode::getLeft() {
    return left;
}

BvhNode * BvhNode::getRight() {
    return right;
}

Box * BvhNode::getBox() {
    return bbox;
}

bool BvhNode::isLeaf() {
    return isLeafFlag;
}

vector<Primitive *> BvhNode::getObjects() {
    return primitives;
}
