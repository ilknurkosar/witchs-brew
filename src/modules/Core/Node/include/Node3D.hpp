#pragma once

#include "Node.hpp"
#include "NodeType.hpp"
#include "raylib.h"
#include "raymath.h"

class Node3D : virtual private NodeType ,public Node{
    public:
        ::Matrix transform = MatrixIdentity();
    public:
        explicit inline Node3D(){this->f |= NodeType::NODE3D;}
};