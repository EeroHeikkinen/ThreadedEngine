#include "physics_tree.hh"


#include <algorithm>
#include <exception>


PhysicsNode::PhysicsNode(
                         PhysicsNode* parent_,
                         PhysicsComponent* component_,
                         PhysicsNode::Childvec children_
                         ) :
    parent(parent_),
    component(component_),
    children(children_) { }

PhysicsNode::PhysicsNode(
                         PhysicsNode* parent_,
                         PhysicsComponent* component_,
                         PhysicsNode* child_
                         ) :
    parent(parent_),
    component(component_) {
	if (child_ != nullptr)
		children.push_back(child_);
}

PhysicsNode::~PhysicsNode() {
	//delete all children (which recursively deletes the whole subtree)
	for (auto i : children) {
		delete i;
	}
	if (parent != NULL)
		parent->removeChild(this);
}

PhysicsNode::Childvec PhysicsNode::getChildren() const {
	return children;
}

PhysicsNode* PhysicsNode::getParent() const {
	return parent;
}

PhysicsComponent* PhysicsNode::getComponent() const {
	return component;
}

void PhysicsNode::setChildren(Childvec newchildren) {
	for (auto i : children) {
		delete i;
	}
	children = newchildren;
}

void PhysicsNode::addChild(PhysicsNode* newchild) {
	children.push_back(newchild);
}

void PhysicsNode::setParent(PhysicsNode* newparent) {
	parent = newparent;
}

bool PhysicsNode::removeChild(PhysicsNode* removed) {
	std::vector<PhysicsNode*>::iterator found = std::find(children.begin(), children.end(), removed);
	if (found != children.end()) {
		children.erase(found);
		return true;
	}
	return false;
}

PhysicsTree::PhysicsTree() {
	root = new PhysicsNode(nullptr, nullptr, nullptr);
}

PhysicsTree::~PhysicsTree() {
	delete root;
}

// Adds node to the tree.
// Child argument should be existing node in the tree.
// In case child is specified the newnode is added between given parent and given child
PhysicsNode* PhysicsTree::addNode(PhysicsNode* parent_, PhysicsComponent* component_, PhysicsNode* child_) {

	PhysicsNode* newnode = new PhysicsNode(parent_, component_, child_);
	parent_->addChild(newnode);
	if (child_ != nullptr) {
		parent_->removeChild(child_);
		//if (found == parent_->getChildren().end())
		//	throw std::logic_error("Child given as parameter is not child of the given parent.");
		newnode->addChild(child_);

	}
	return newnode;
}

void PhysicsTree::removeNode(PhysicsNode* node) {
	node->getParent()->removeChild(node);
	delete node;
}

PhysicsNode* PhysicsTree::getRoot() const {
	return root;
}