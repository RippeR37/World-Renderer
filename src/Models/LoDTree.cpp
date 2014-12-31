#include "LoDTree.h"

namespace Model {

    LoDTree::LoDTree() {
        parent = nullptr;
        child[0] = child[1] = child[2] = child[3] = nullptr;
    }

    LoDTree::LoDTree(void* pOffset, unsigned int pCount) {
        parent = nullptr;
        child[0] = child[1] = child[2] = child[3] = nullptr;

        offset = pOffset;
        count  = pCount;
    }

    LoDTree::~LoDTree() {
        for(int i = 0; i < 4; ++i) {
            if(child[i] != nullptr)
                delete child[i];
        }
    }

}