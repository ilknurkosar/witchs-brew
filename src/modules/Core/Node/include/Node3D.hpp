#pragma once

#include "Node.hpp"
#include "raylib.h"
#include "raymath.h"

class Node3D : virtual public Node{
    public:
        ::Matrix transform = MatrixIdentity();
    public:
        explicit inline Node3D(){this->tFlags |= TF_3D;}
};