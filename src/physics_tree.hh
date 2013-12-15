#ifndef PHYSICS_TREE_HH
#define PHYSICS_TREE_HH

#include <vector>

class PhysicsComponent;


//treenode
class PhysicsNode{
public:
    typedef std::vector<PhysicsNode*> ChildVec;

    PhysicsNode(PhysicsNode* parent_,
                PhysicsComponent* component_,
                ChildVec children_ = ChildVec());
    PhysicsNode(PhysicsNode* parent_,
                PhysicsComponent* component_,
                PhysicsNode* child_);
    ~PhysicsNode();

    ChildVec getChildren() const;
    PhysicsNode* getParent() const;
    PhysicsComponent* getComponent() const;

    void setChildren(ChildVec);
    void addChild(PhysicsNode*);
    void setParent(PhysicsNode*);
    bool removeChild(PhysicsNode*);
private:
    PhysicsNode* pParent;
    PhysicsComponent* pComponent;
    ChildVec vpChildren;
};

class PhysicsTree {
public:
    PhysicsTree();
    ~PhysicsTree();

    PhysicsNode* addNode(PhysicsNode* parent, PhysicsComponent* component, PhysicsNode* child = nullptr);
    void removeNode(PhysicsNode*);

    PhysicsNode* getRoot() const;

    PhysicsTree(const PhysicsTree&) = delete;
    PhysicsTree& operator=(PhysicsTree&) = delete;
private:
    void destroyTree(PhysicsNode* node);
	PhysicsNode* root;
};


#endif // PHYSICS_TREE_HH
