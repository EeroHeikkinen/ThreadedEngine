#include "physics_tree.hh"

#include <algorithm>


PhysicsNode::PhysicsNode(PhysicsNode* pParent,
                         PhysicsComponent* pComponent,
                         PhysicsNode::ChildVec _vpChildren) :
    pParent(pParent),
    pComponent(pComponent),
    vpChildren(std::move(_vpChildren))
    {}

PhysicsNode::PhysicsNode(PhysicsNode* pParent,
                         PhysicsComponent* pComponent,
                         PhysicsNode* pChild) :
    pParent(pParent),
    pComponent(pComponent)
    {
        if(pChild != nullptr)
            vpChildren.push_back(pChild);
    }

PhysicsNode::~PhysicsNode(){
	//delete all children (which recursively deletes the whole subtree)

	if (pParent != NULL)
		for (auto pChild : vpChildren){
			pParent->addChild(pChild);
		}
		pParent->removeChild(this);
}

PhysicsNode::ChildVec PhysicsNode::getChildren() const{
	return vpChildren;
}

PhysicsNode* PhysicsNode::getParent() const{
	return pParent;
}

PhysicsComponent* PhysicsNode::getComponent() const{
	return pComponent;
}

void PhysicsNode::setChildren(ChildVec newchildren){
	for (auto pChild : vpChildren)
		delete pChild;

	vpChildren = std::move(newchildren);
}

void PhysicsNode::addChild(PhysicsNode* newchild){
	vpChildren.push_back(newchild);
}

void PhysicsNode::setParent(PhysicsNode* newparent){
	pParent = newparent;
}

bool PhysicsNode::removeChild(PhysicsNode* removed) {
	std::vector<PhysicsNode*>::iterator found = std::find(vpChildren.begin(), vpChildren.end(), removed);
	if (found != vpChildren.end()){
		vpChildren.erase(found);
		return true;
	}
	return false;
}

PhysicsTree::PhysicsTree(){
	root = new PhysicsNode(nullptr, nullptr, nullptr);
}

PhysicsTree::~PhysicsTree(){
}

// Adds node to the tree.
// Child argument should be existing node in the tree.
// In case child is specified the newnode is added between given parent and given child
PhysicsNode* PhysicsTree::addNode(PhysicsNode* parent_, PhysicsComponent* component_, PhysicsNode* child_){
	PhysicsNode* newnode = new PhysicsNode(parent_, component_, child_);
	parent_->addChild(newnode);
	if (child_ != nullptr){
		parent_->removeChild(child_);
		//if (found == parent_->getChildren().end())
		//	throw std::logic_error("Child given as parameter is not child of the given parent.");
		newnode->addChild(child_);
	}
	return newnode;
}

void PhysicsTree::removeNode(PhysicsNode* node){
	delete node;
}

PhysicsNode* PhysicsTree::getRoot() const{
	return root;
}
