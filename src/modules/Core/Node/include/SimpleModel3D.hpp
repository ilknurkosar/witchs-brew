#pragma once

#include "MaterialResource.hpp"
#include "MeshResource.hpp"
#include "Node3D.hpp"
#include "VisualNode.hpp"
#include "NodeType.hpp"
#include "SimpleModelResource.hpp"
#include "raylib.h"
#include "raymath.h"

class SimpleModel3D : virtual private NodeType, public VisualNode, public Node3D{
    protected:
        Color color = WHITE;
        SimpleModelResource *smodel = nullptr;
    public:
        explicit inline SimpleModel3D() {this->f |= NodeType::SIMPLEMODEL3D;}
        explicit inline SimpleModel3D(SimpleModelResource* smodel)
        : SimpleModel3D()
        {
            this->smodel = smodel;
        }
        explicit inline SimpleModel3D(SimpleModelResource* smodel, Color color)
        : SimpleModel3D(smodel)
        {
            this->color = color;
        }
        inline bool isNull() const {return smodel == nullptr;}
        inline void setColor(Color color){this->color = color;}
        inline Color getColor(){return color;}
        inline void setModel(SimpleModelResource* model){this->smodel = model;}
        inline SimpleModelResource* getModel(){return smodel;}
};