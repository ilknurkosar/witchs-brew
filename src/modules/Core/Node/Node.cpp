#include "Node.hpp"
#include <vector>

Node::Node() :
isEnabled(true),
isProcessed(false),
isVisible(false),
parent(nullptr),
children()
{

}

std::vector<Node*>& Node::getChildren(){
    return children;
}

Node* Node::getParent(){
    return parent;
}
void Node::process(double delta){
    return; // do nothing
}