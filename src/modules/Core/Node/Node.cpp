#include "Node.hpp"
#include <algorithm>
#include <memory>
#include <vector>

void Node::removeChild(Node* n){
    std::vector<std::unique_ptr<Node>>::iterator res = children.begin();
    if((res = std::find_if(children.begin(),children.end(),
        [&](std::unique_ptr<Node> &v)-> bool{
            return v.get() == n;
        })) != children.end()){
            std::unique_ptr<Node> &temp= children.at(res - children.begin());
            n = temp.release();
            children.erase(res);
        }
}

void Node::setParent(Node* parent){
    if(this->parent == parent)
        return;
    Node* oldparent = this->parent;
    if (oldparent != nullptr) {
        oldparent->removeChild(this);
    }
    this->parent = parent;
    if(parent != nullptr)
        parent->getChildren().push_back(std::unique_ptr<Node>(this));
}

// void Node::Init(void** data){return;}
// void Node::DeInit(){return;}