#ifndef PHYSICS_TREE_HH
#define PHYSICS_TREE_HH

#include "component.hh"

#include <vector>


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

/*
    //iterator base class from which different iterators can be derived.
    template<bool is_const_iterator = true>
    class PhysicsTreeIterator : public std::iterator<std::forward_iterator_tag, PhysicsComponent*> {

    public:
        //typedefs to make the iterator either const or non-const
        virtual PhysicsTreeIterator() {}
        typedef typename std::conditional<is_const_iterator, const Node, Node> iterator_node;
        typedef typename std::conditional<is_const_iterator, const PhysicsComponent, PhysicsComponent> iterator_component;

        virtual ~PhysicsTreeIterator() {}

        iterator_component operator*() const;
        bool operator==(const PhysicsTreeIterator) const;
        bool operator!=(const PhysicsTreeIterator) const;



    protected:
        virtual void operator++() = 0;
        virtual void operator++(int) = 0;

        iterator_node* current;
    };

    //typedefs to define const_iterator and iterator for the tree
    typedef PhysicsTreeIterator<true> const_iterator;
    typedef PhysicsTreeIterator<false> iterator;

*/
