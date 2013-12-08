#include "entity.hh"


void Entity::eraseChild(Entity* pChild){
    mpChildren.erase(pChild);
}

void Entity::eraseThisSubtree(void){
    if(parent == nullptr)
        return; //this shouldn't happen; one should never erase the Universe explicitly
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

