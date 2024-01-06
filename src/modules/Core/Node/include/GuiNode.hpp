#pragma once

#include "Node2D.hpp"
#include "NodeType.hpp"
#include "VisualNode.hpp"
#include "raygui-implement.h"

class GuiNode : public VisualNode, public Node2D{
    protected:
    public:
        explicit inline GuiNode() {setFlag(NodeType::GUI);}
        virtual void display(Matrix transform) = 0;
        virtual ~GuiNode() = default;
};