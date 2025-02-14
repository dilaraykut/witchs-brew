#include "Scene.hpp"
#include "Node.hpp"
#include "RunnableNode.hpp"
#include "VisualNode.hpp"
#include <functional>
#include <memory>
#include <vector>

//TODO: Write tests for this class

Scene *Scene::singleton=nullptr;

std::vector<VisualNode*> Scene::getVisual(){
    std::vector<VisualNode*> out{};

    std::function<void(Node*)> recurseChild = [&](Node* n) -> void{
        if(n->checkType(NodeType::VISUAL))
            out.push_back((VisualNode*)n);
        std::vector<std::unique_ptr<Node>> &childs = n->getChildren();
        for(std::unique_ptr<Node> &c: childs){
            if(c->isVisible())
                recurseChild(c.get());
        }
    };

    std::vector<std::unique_ptr<Node>> &orphans = Scene::getRoot().getChildren();

    for(std::unique_ptr<Node> &orphan: orphans){
        if(orphan->isVisible())
            recurseChild(orphan.get());
    }
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

    std::vector<std::unique_ptr<Node>> &orphans = Scene::getRoot().getChildren();

    for(std::unique_ptr<Node> &orphan: orphans){
        if(orphan->isEnabled())
            recurseChild(orphan.get());
    }
    return out;
}

Scene::Scene(){
    singleton = this;
}
Scene::~Scene(){
    singleton = nullptr;
}

void Scene::addNode(Node *n){
    if(n == nullptr)
        return;
    n->setParent(&Scene::getRoot());
}

Node& Scene::getRoot(){
    return singleton->root;
}