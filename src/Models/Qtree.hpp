#ifndef MODEL_QTREE_HPP_INCLUDED
#define MODEL_QTREE_HPP_INCLUDED

#include "QTree.h"

namespace Model {

    template<typename T>
    QTree<T>::QTree() {
        for(auto& childPtr : child)
            childPtr = nullptr;

        this->parent = nullptr;
    }
    
    template<typename T>
    QTree<T>::QTree(const T& value) {
        for(auto& childPtr : child)
            childPtr = nullptr;

        this->parent = nullptr;
        this->data = value;
    }
    
    template<typename T>
    QTree<T>::~QTree() {
        for(auto& childPtr : child) {
            if(childPtr != nullptr) {
                delete childPtr;
                childPtr = nullptr;
            }
        }
    }

}

#endif