#pragma once

#include "Node.hpp"

class VisualNode : virtual public Node{
    public:
        inline VisualNode(){this->tFlags |= TF_VISUAL;}
};