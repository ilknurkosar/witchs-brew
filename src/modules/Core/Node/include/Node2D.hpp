#pragma once

#include "Node.hpp"
#include "raylib.h"
#include "raymath.h"

class Node2D : virtual public Node{
    public:
        ::Matrix transform = MatrixIdentity(); // it makes no sense to use this in 2D but raylib has no 3x3 matrix
    public:
        inline Node2D(){this->tFlags |= TF_2D;}
};