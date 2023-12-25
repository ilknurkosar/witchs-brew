#pragma once

#include "NodeType.hpp"
class VisualNode : virtual private NodeType{
    public:
        inline VisualNode(){this->f |= NodeType::VISUAL;}
};