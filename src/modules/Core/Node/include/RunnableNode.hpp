#pragma once

#include "NodeType.hpp"
#include "Runnable.hpp"

class RunnableNode : virtual private NodeType, public Runnable {
    public:
        inline RunnableNode(){this->f |= NodeType::PROCESSABLE;}
};