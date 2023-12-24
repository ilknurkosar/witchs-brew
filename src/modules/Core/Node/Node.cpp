#include "Node.hpp"
#include <vector>

void Node::setParent(Node* parent){
    this->parent = parent;
    if(parent != nullptr)
        parent->getChildren().push_back(this);
}

