#include "entity.hh"


void Entity::eraseThisSubtree(void){
    if(pParent == nullptr)
        return; //this shouldn't happen; one should never erase the Universe explicitly
    pParent->eraseChild(this);
}

void Entity::eraseThisAlone(void){
    for(auto& pChildPair : mpChildren){
        pChildPair.first->pParent = this->pParent;
        this->pParent->addChild(std::move(pChildPair.second));
    }
    eraseThisSubtree();
}

void Entity::addComponent(std::unique_ptr<Component> pComponent){
    lpComponents.emplace_front(std::move(pComponent));
}

void Entity::eraseChild(Entity* pChild){
    mpChildren.erase(pChild);
}
