#pragma once

#include "NodeType.hpp"
class VisualNode : virtual public NodeType{
    public:
        inline VisualNode(){setFlag(NodeType::VISUAL);}
};