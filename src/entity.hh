#include <memory>
#include <list>
#include <unordered_map>

class Entity{
public:
    Entity(void);
    virtual ~Entity();
    Entity(const Entity&) = delete; //add these later
    Entity& operator=(const Entity&) = delete;

    template<typename DerivedEntity>
    DerivedEntity* addChild(std::unique_ptr<DerivedEntity>);

    void eraseChild(Entity*);
    void eraseThisTree(void);
    void eraseThisAlone(void);

    void addComponent(std::unique_ptr<Component>);
    //if you think that you need to delete a component, go kill yourself

protected:
    Entity* pParent;
    std::list<std::unique_ptr<Component>> lpComponents;
    std::unordered_map<Entity*, std::unique_ptr<Entity>> mpChildren;
};

template<typename DerivedEntity>
DerivedEntity* Entity::addChild(std::unique_ptr<DerivedEntity> pChild){
    DerivedEntity* pAdded = pChild.get();
    if(pAdded == nullptr)
        return nullptr;

    pChild->parent = this;
    mpChildren.emplace(pAdded, std::move(pChild));
    return pAdded;
}
