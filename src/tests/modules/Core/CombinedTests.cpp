#include "MainLoop.hpp"
#include "NodeType.hpp"
#include "Scene.hpp"
#include <gtest/gtest.h>

TEST(SceneTest, check_root){
    Scene s{};
    Node* r = Scene::getRoot();
    ASSERT_FALSE( r->checkType(NodeType::NODE2D));
}
TEST(SceneTest, check_recursion){
    Scene s{};
    Node* r = Scene::getRoot();
    Node* c = new Node();
    Scene::addNode(c);
    ASSERT_TRUE(c->getParent() == r);
    int count = 0;
    for(Node* p = c->getParent(); p != nullptr; p = p->getParent()){
        count++;
    }
    ASSERT_EQ(count, 1);
}