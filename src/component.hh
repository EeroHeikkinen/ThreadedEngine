#ifndef COMPONENT_HH
#define COMPONENT_HH

#include "physics_motion_state.hh"
#include "make_unique.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicsNode;


class Component{
public:
    Component(){}
    virtual ~Component(){}
};

//StupidRenderComponent
class StupidRenderComponent : public Component{
public:
    StupidRenderComponent(void){}
    virtual ~StupidRenderComponent(void){}

    virtual void render(const glm::mat4&, const glm::mat4&) = 0;

    RenderComponent(const RenderComponent&) = delete;
    RenderComponent& operator=(const RenderComponent&) = delete;
protected:
    /* For successful threading, these two      *
     * functions shall be called in the most    *
     * derived class constructor and destructor *
     * and NEVER OVERRIDDEN!                    */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename RenderFunc>
class _StupidRenderComponent : public StupidRenderComponent{
public:
    _StupidRenderComponent(RenderFunc rfunc) :
        rfunc(rfunc)
        {
            addToStructure();
        }
    ~_StupidRenderComponent(void){ //FINAL
        removeFromStructure();
    }

    void render(const glm::mat4& view, const glm::mat4& proj){
        rfunc(view, proj);
    }
private:
    RenderFunc rfunc;
};
template<typename RenderFunc>
std::unique_ptr<_StupidRenderComponent<RenderFunc>>
makeStupidRenderComponent(RenderFunc rfunc){
    return make_unique<_StupidRenderComponent<RenderFunc>>(rfunc);
}

//LogicComponent
class LogicComponent : public Component{
public:
    LogicComponent(void);
    virtual ~LogicComponent(void);

    virtual void logic(void) = 0;

    LogicComponent(const LogicComponent&) = delete;
    LogicComponent& operator=(const LogicComponent&) = delete;
protected:
    /* For successful threading, these two      *
     * functions shall be called in the most    *
     * derived class constructor and destructor *
     * and NEVER OVERRIDDEN!                    */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename LogicFunc>
class _LogicComponent : public LogicComponent{
public:
    _LogicComponent(LogicFunc lfunc) :
        lfunc(lfunc)
        {
            addToStructure();
        }
    ~_LogicComponent(void){ //FINAL
        removeFromStructure();
    }

    void logic(void){
        lfunc();
    }
private:
    LogicFunc lfunc;
};
template<typename LogicFunc>
std::unique_ptr<_LogicComponent<LogicFunc>>
makeLogicComponent(LogicFunc lfunc){
    return make_unique<_LogicComponent<LogicFunc>>(lfunc);
}

//PhysicsComponent
class PhysicsComponent : public Component{
public:
    PhysicsComponent(std::unique_ptr<btCollisionShape> pCollisionMesh,
                     PhysicsNode* pParent,
                     glm::vec3 initialPos,
                     glm::vec3 initialVel,
                     glm::mat4& model,
                     float mass,
                     float restitution);
    virtual ~PhysicsComponent(void);

    void setTransformation(const btTransform& worldTrans);

    PhysicsComponent(const PhysicsComponent&) = delete;
    PhysicsComponent& operator=(const PhysicsComponent&) = delete;
protected:
    std::unique_ptr<btCollisionShape> pCollisionMesh;
    std::unique_ptr<PhysicsMotionState> pMotionState;
    PhysicsNode* node;
    glm::vec3 initialPos;
    glm::mat4& model;
    float mass;
    std::unique_ptr<btRigidBody> pPhysicsBody;

    /* For successful threading, these two      *
     * functions shall be called in the most    *
     * derived class constructor and destructor *
     * and NEVER OVERRIDDEN!                    */
    void addToStructure(void);
    void removeFromStructure(void);
};


#endif // COMPONENT_HH
