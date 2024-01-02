#pragma once

#include "Node.hpp"
#include "Runnable.hpp"
#include "RunnableNode.hpp"
#include "VisualNode.hpp"
#include <vector>

class Scene : public Runnable{
private:
    static Scene *singleton;
    Node root;
public:
    static void addNode(Node* n);
    static Node* getRoot();
    static inline Scene* getSingleton(){return singleton;}
    static std::vector<Node*> getVisual();
    static std::vector<RunnableNode*> getRunnable();
    // There is no removal. Nodes delete themselves
    // TODO: except they dont, fix it later

    virtual void process(double delta) override;

    explicit Scene();
    ~Scene();
    friend Node; //so the nodes can remove themselves
};
/*
// Scene class holding orphan nodes
class Scene {
private:
    std::vector<Node*> nodes;

public:
    void addNode(Node* node) {
        nodes.push_back(node);
    }

    // Process all enabled nodes and their children
    void process() {
        for (Node* node : nodes) {
            if (node->isEnabled()) {
                processNodeAndChildren(node);
            }
        }
    }

    // Render visible nodes
    std::vector<VisualNode*> getVisibleNodes() const {
        std::vector<VisualNode*> visibleNodes;
        for (Node* node : nodes) {
            if (node->checkType(NodeType::VISUAL) && node->isVisible()) {
                visibleNodes.push_back(static_cast<VisualNode*>(node));
            }
        }
        return visibleNodes;
    }

private:
    // Recursively process node and its children
    void processNodeAndChildren(Node* node) {
        if (node->checkType(NodeType::PROCESSABLE)) {
            // Call process() only if it is a RunnableNode
            static_cast<RunnableNode*>(node)->process();
        }

        // Process children
        for (Node* child : getChildren(node)) {
            processNodeAndChildren(child);
        }
    }

    // Helper function to get children of a node
    std::vector<Node*> getChildren(Node* parent) const {
        // For simplicity, return an empty vector here
        // In a real scenario, you would need a mechanism to manage parent-child relationships
        return {};
    }
};
*/