#pragma once

#include "NodeType.hpp"
#include <cstdint>
#include <vector>

class Node : virtual private NodeType { // Inheriting Runnable is now optional
    public:
    protected:
        std::vector<Node*> children{};
        Node* parent = nullptr;
        bool enabled = true; //stops children from being processed
        bool visible = true; //stops children from being rendered
    public:
        inline Node* getParent(){return parent;}
        void setParent(Node* parent);
        inline std::vector<Node*>& getChildren(){ return children;}
        inline bool isEnabled(){return enabled;}
        void enable();
        void disable();
        inline bool isVisible(){return visible;}
        void makeVisible();
        void makeInvisible();
        inline bool checkType(NodeType::FLAG f){return this->f & f;}
        explicit Node() = default;
        virtual ~Node() = default;
    protected:
};