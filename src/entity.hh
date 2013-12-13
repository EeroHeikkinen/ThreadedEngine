#ifndef ENTITY_HH
#define ENTITY_HH

#include "component.hh"

#include <memory>
#include <list>
#include <unordered_map>


class Entity{
public:
    Entity(void) : pParent(nullptr) {}
    virtual ~Entity(){}
    Entity(const Entity&) = delete; //add these later
    Entity& operator=(const Entity&) = delete;

    template<typename DerivedEntity>
    DerivedEntity* addChild(std::unique_ptr<DerivedEntity>);

    void eraseThisSubtree(void);
    void eraseThisAlone(void);

    void addComponent(std::unique_ptr<Component>);
    //if you think that you need to delete a component, go kill yourself

    void registerComponents(void);
    void unregisterComponents(void);
protected:
    Entity* pParent;
    std::list<std::unique_ptr<Component>> lpComponents;
    std::unordered_map<Entity*, std::unique_ptr<Entity>> mpChildren;

    void eraseChild(Entity*);
};

template<typename DerivedEntity>
DerivedEntity* Entity::addChild(std::unique_ptr<DerivedEntity> pChild){
    DerivedEntity* pAdded = pChild.get();
    if(pAdded == nullptr)
        return nullptr; //this means the user is somewhat stupid

    pChild->pParent = this;
    mpChildren.emplace(pAdded, std::move(pChild));
    return pAdded;
}


#endif //ENTITY_HH
