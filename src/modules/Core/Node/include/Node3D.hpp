#pragma once

#include "Node.hpp"
#include "NodeType.hpp"
#include "raylib.h"
#include "raymath.h"

class Node3D : public Node{
    public:
        ::Matrix t = MatrixIdentity(); // the transformation
    public:
        explicit inline Node3D() : Node() {setFlag(NodeType::NODE3D);}
        virtual ~Node3D() = default;
};