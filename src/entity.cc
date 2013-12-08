#include "entity.hh"

Entity::Entity(void){}

virtual Entity::~Entity(){}

void Entity::eraseChild(Entity* pChild){
    mpChildren.erase(pChild);
}

void Entity::eraseThisTree(void){
    if(parent == nullptr)
        return; //this shouldn't happen
    parent->eraseChild(this);
}

void Entity::eraseThisAlone(void){
    for(auto& pChildPair : mpChildren){
        pChildPair.first->parent = this->parent;
        this->parent->addChild(std::move(pChildPair.second));
    }
    eraseThisTree();
};

void Entity::addComponent(std::unique_ptr<Component> pComponent){
    lpComponents.emplace_front(std::move(pComponent));
}

