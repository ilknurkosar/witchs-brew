#pragma once

#include "NodeType.hpp"
#include <cstdint>
#include <vector>

class Node : virtual private NodeType {
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
        inline void enable(){enabled = true;}
        inline void disable(){enabled = false;}
        inline bool isOrphan(){return parent == nullptr;}
        inline bool isVisible(){return visible;}
        inline void makeVisible(){visible = true;}
        inline void makeInvisible(){visible = false;}
        inline bool checkType(NodeType::FLAG f){return this->f & f;}
        virtual void Init(void** data); // 2-stage constructor separate from constructor
        virtual void DeInit(); // 2-stage deconstructor separate from deconstructor
        explicit inline Node() : NodeType(){};
        explicit Node(const Node &) = delete;
        explicit Node(Node &&) = delete;
        Node &operator=(Node &&) = default;
        Node &operator=(const Node &) = default;
        virtual ~Node() = default;
    protected:
};