#pragma once

#include "NodeType.hpp"
#include <memory>
#include <vector>

class Node : virtual public NodeType {
    public:
    protected:
        std::vector<std::unique_ptr<Node>> children{};
        Node* parent = nullptr;
        bool enabled = true; //stops children from being processed
        bool visible = true; //stops children from being rendered
    public:
        inline Node* getParent(){return parent;}
        void setParent(Node* parent);
        inline std::vector<std::unique_ptr<Node>>& getChildren(){ return children;}
        inline bool isEnabled(){return enabled;}
        inline void enable(){enabled = true;}
        inline void disable(){enabled = false;}
        inline bool isOrphan(){return parent == nullptr;}
        inline bool isVisible(){return visible;}
        inline void makeVisible(){visible = true;}
        inline void makeInvisible(){visible = false;}
        virtual void Init(void** data); // 2-stage constructor separate from constructor
        virtual void DeInit(); // 2-stage deconstructor separate from deconstructor
        explicit inline Node() : NodeType(){};
        explicit Node(const Node &) = delete;
        explicit Node(Node &&) = delete;
        Node &operator=(Node &&) = default;
        Node &operator=(const Node &) = default;
        virtual ~Node() = default;
    protected:
        void removeChild(Node* n);
};