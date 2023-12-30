#pragma once

#include "NodeType.hpp"
#include "Runnable.hpp"

class RunnableNode : virtual public NodeType, public Runnable {
    public:
        inline RunnableNode(){setFlag( NodeType::PROCESSABLE);}
};