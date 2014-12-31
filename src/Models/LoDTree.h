#ifndef MODEL_LODTREE_H_INCLUDED
#define MODEL_LODTREE_H_INCLUDED

namespace Model {

    struct LoDTree {
        LoDTree();
        LoDTree(void* pOffset, unsigned int pCount);
        ~LoDTree();

        LoDTree* parent;
        LoDTree* child[4];

        float x, y, z;
        float width;

        void* offset;           // IBO pointer data
        unsigned int count;     // IBO pointer data
    };

}

#endif