#include "Scene.hpp"
#include "Node.hpp"
#include "RunnableNode.hpp"
#include "VisualNode.hpp"
#include <functional>
#include <memory>
#include <vector>

//TODO: Write tests for this class

Scene *Scene::singleton=nullptr;

void Scene::process(double delta){
    auto runnables = getRunnable();
    for (auto runnable : runnables) {
        runnable->process(delta);
    }
}

std::vector<Node*> Scene::getVisual(){
    std::vector<Node*> out{};

    std::function<void(Node*)> recurseChild = [&](Node* n) -> void{
        if(n->checkType(NodeType::VISUAL))
            out.push_back((Node*)n);
        std::vector<std::unique_ptr<Node>> &childs = n->getChildren();
        for(std::unique_ptr<Node> &c: childs){
            if(c->isVisible())
                recurseChild(c.get());
        }
    };

    recurseChild(Scene::getRoot());
    return out;
}
std::vector<RunnableNode*> Scene::getRunnable(){
    std::vector<RunnableNode*> out{};

    std::function<void(Node*)> recurseChild = [&](Node* n) -> void{
        if(n->checkType(NodeType::PROCESSABLE))
            out.push_back((RunnableNode*)n);
        std::vector<std::unique_ptr<Node>> &childs = n->getChildren();
        for(std::unique_ptr<Node> &c: childs){
            if(c->isEnabled())
                recurseChild(c.get());
        }
    };

    recurseChild(Scene::getRoot());
    return out;
}

Scene::Scene()
: root()
{
    singleton = this;
}
Scene::~Scene(){
    singleton = nullptr;
}

void Scene::addNode(Node *n){
    // if(n == nullptr) //intentionally removed safeguard
    //     return;
    n->setParent(Scene::getRoot());
}

Node* Scene::getRoot(){
    return &singleton->root;
}