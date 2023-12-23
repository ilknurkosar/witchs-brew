#pragma once

#include "Runnable.hpp"
#include <vector>

class Node : public Runnable {
    public:
        bool isEnabled; //stops children from being rendered/processed
        bool isProcessed;
        bool isVisible;
    protected:
        Node* parent;
        std::vector<Node*> children;
    public:
        virtual void process(double delta) override;
        Node* getParent();
        std::vector<Node*>& getChildren();
        Node();
        virtual ~Node() = default;
    protected:
};