#pragma once

#include "Node2D.hpp"
#include "Node3D.hpp"
#include "VisualNode.hpp"
#include "raylib.h"
#include <type_traits>
#include <vector>

// exclusive for 2D or 3D visual nodes
template<class T> class PackedNodes{
    static_assert(std::is_base_of<VisualNode, T>(), "T must inherit VisualNode");
    static_assert(std::is_base_of<Node2D, T>() ^ std::is_base_of<Node3D, T>(), "T must inherit Node2D or Node3D");

    private:
    int size{0};
    std::vector<T*> nodes{};
    std::vector<::Matrix> transforms{};
    public:
    explicit inline PackedNodes() {}
    inline int length() {return size;}
    inline void add(T* node, ::Matrix transform){
        nodes.push_back(node);
        transforms.push_back(transform);
        size++;
    }
    inline T* getNode(int i){
        return nodes[i];
    }
    inline ::Matrix getTranform(int i){
        return transforms[i];
    }
    inline void clear(){
        nodes.clear();
        transforms.clear();
        size = 0;
    }
};