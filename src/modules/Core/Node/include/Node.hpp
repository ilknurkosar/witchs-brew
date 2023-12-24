#pragma once

#include <cstdint>
#include <vector>

class Node { // Inheriting Runnable is now optional
    public:
        enum TYPEFLAG
        {
            TF_PROCESSABLE = 1 << 0,
            TF_VISUAL = 1 << 1,
            TF_2D = 1 << 2,
            TF_3D = 1 << 3,
            TF_MODEL3D = 1 << 4,
            TF_CAMERA3D = 1 << 5,
            TF_TEXTURE2D = 1 << 6,
            TF_TEXT2D = 1 << 7,
            TF_TEXT3D = 1 << 8,
        };
    protected:
        std::vector<Node*> children{};
        Node* parent = nullptr;
        uint32_t tFlags = 0;
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
        inline bool checkType(Node::TYPEFLAG f){return tFlags & f;}
        explicit Node() = default;
        virtual ~Node() = default;
    protected:
};