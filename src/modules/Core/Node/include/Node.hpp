#pragma once

#include "NodeType.hpp"
#include "Runnable.hpp"
#include <memory>
#include <string>
#include <vector>

class Node : virtual public NodeType, public Runnable {
    public:
        std::string name;
    protected:
        std::vector<std::unique_ptr<Node>> children{};
        Node* parent = nullptr;
        bool enabled = true; //stops children from being processed
        bool visible = true; //stops children from being rendered
    public:
        virtual void process(double delta) override;

        inline Node* getParent(){return parent;}
        void setParent(Node* parent);
        Node* findChild(std::string name);
        inline std::vector<std::unique_ptr<Node>>& getChildren(){ return children;}
        inline bool isEnabled(){return enabled;}
        inline void enable(){enabled = true;}
        inline void disable(){enabled = false;}
        inline bool isOrphan(){return parent == nullptr;}
        inline bool isVisible(){return visible;}
        inline void makeVisible(){visible = true;}
        inline void makeInvisible(){visible = false;}
        explicit inline Node() =default;
        explicit inline Node(std::string name): Node(){this->name = name;}
        explicit Node(const Node &) = delete;
        explicit Node(Node &&) = delete;
        Node &operator=(Node &&) = default;
        Node &operator=(const Node &) = default;
        virtual ~Node();
    protected:
        void removeChild(Node* n);
};