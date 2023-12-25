#include "Node.hpp"
#include "Node3D.hpp"
#include "NodeType.hpp"
#include "Vector3.hpp"
#include "raylib.h"
#include <cstdint>
#include <gtest/gtest.h>
#include "raylib-wrap.hpp"

TEST(Node_basic, default_constructor){
    Node n{};
    ASSERT_TRUE(n.isEnabled());
    ASSERT_TRUE(n.isVisible());
    ASSERT_FALSE(n.checkType(NodeType::PROCESSABLE));
}
TEST(Node_basic, paternity_test){
    Node p{};
    Node c{};
    c.setParent(&p);
    ASSERT_EQ(p.getChildren().size(), 1);
    ASSERT_TRUE(p.getChildren().front() == &c);
    ASSERT_EQ(c.getParent(), &p);
}

TEST(Node_3D, flag_check){
    Node3D n{};
    ASSERT_TRUE(n.checkType(NodeType::NODE3D));
}
// TEST(Node_3D, matirx_check){ // I hate raylib with passion now
//     Node3D n{};
//     ::Vector4 v = {1.0};
//     ASSERT_EQ(n.transform * v, raylib::Vector4{1.0});
// }
TEST(Node_3D, matirx_check){
    Node3D n{};
    ::Vector3 v = {1.0};
    ASSERT_EQ(raylib::Vector3{n.transform * v}, raylib::Vector3{1.0});
}
TEST(Node_3D, paternity_test){
    Node p{};
    Node3D n{};
    n.setParent(&p);
    ASSERT_TRUE(p.getChildren().front()->checkType(NodeType::NODE3D));
}