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

void Entity::registerComponents(void){
    for(auto& pComponent : lpComponents){
        if(!pComponent->isInStructure){
            pComponent->addToStructure();
            pComponent->isInStructure = true;
        }
    }
}
void Entity::unregisterComponents(void){
    for(auto& pComponent : lpComponents){
        if(pComponent->isInStructure){
            pComponent->removeFromStructure();
            pComponent->isInStructure = false;
        }
    }
}

void Entity::eraseChild(Entity* pChild){
    mpChildren.erase(pChild);
}
