#pragma once

#include "Node.hpp"
#include "NodeType.hpp"
#include "raylib.h"
#include "raymath.h"

class Node2D : virtual private NodeType ,public Node{
    public:
        ::Matrix t = MatrixIdentity(); // it makes no sense to use this in 2D but raylib has no 3x3 matrix
    public:
        inline Node2D(){this->f |= NodeType::NODE2D;}
};