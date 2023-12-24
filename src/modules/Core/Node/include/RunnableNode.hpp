#pragma once

#include "Node.hpp"
#include "Runnable.hpp"

class RunnableNode : virtual public Node, public Runnable {
    public:
        inline RunnableNode(){this->tFlags |= TF_PROCESSABLE;}
};