#pragma once

#include "NodeType.hpp"
#include "Runnable.hpp"

class RunnableNode : virtual public NodeType{
//TODO: figure out a way to make this inherit Runnable instead of Node itselff, without breaking the code
    public:
        inline RunnableNode(){setFlag( NodeType::PROCESSABLE);}
};