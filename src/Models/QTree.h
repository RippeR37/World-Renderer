#ifndef MODEL_QTREE_H_INCLUDED
#define MODEL_QTREE_H_INCLUDED

namespace Model {

    template <typename T>
    class QTree {
        public:
            QTree();
            QTree(const T& data);
            ~QTree();

        public:
            QTree* parent;
            QTree* child[4];

        public:
            T data;
    };

}

#include "Qtree.hpp"

#endif