#ifndef NODE_HPP_
#define NODE_HPP_

#include "Index2D.hpp"

struct Node {
    Index2D indPos;
    int indId;
    Node * adjacents[4];   // [0] = UP, [1] = RIGHT, [2] = DOWN, [3] = LEFT
    Node * parent;
    bool traversable;
    Node() 
    : indId(-1)
    , adjacents{nullptr, nullptr, nullptr, nullptr}
    , parent(nullptr)
    , traversable(true) 
    {}
};

#endif