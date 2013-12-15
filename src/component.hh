#ifndef COMPONENT_HH
#define COMPONENT_HH

#include "make_unique.hh"
#include "physics_utils.hh"

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>

class PhysicsNode;
namespace Test{class StupidRenderer;}


class Component{
public:
    Component(void) : isInStructure(false) {}
    virtual ~Component(void){}

    virtual void addToStructure(void) = 0;
    virtual void removeFromStructure(void) = 0;

    /* Modify this and I'll strangle you */
    bool isInStructure;
};

//StupidRenderComponent
class StupidRenderComponent : public Component{
public:
    StupidRenderComponent(Test::StupidRenderer* pTargetStructure) :
        pTargetStructure(pTargetStructure)
        {}
    virtual ~StupidRenderComponent(void){}

    virtual void render(const glm::mat4&, const glm::mat4&) = 0;

    StupidRenderComponent(const StupidRenderComponent&) = delete;
    StupidRenderComponent& operator=(const StupidRenderComponent&) = delete;
protected:
    Test::StupidRenderer* pTargetStructure;

    /* NEVER OVERRIDE! */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename RenderFunc>
class _StupidRenderComponent : public StupidRenderComponent{
public:
    _StupidRenderComponent(Test::StupidRenderer* pTargetStructure,
                           RenderFunc _rfunc) :
        StupidRenderComponent(pTargetStructure),
        rfunc(std::move(_rfunc))
        {}

    void render(const glm::mat4& view, const glm::mat4& proj){
        rfunc(view, proj);
    }
private:
    RenderFunc rfunc;
};
template<typename RenderFunc>
std::unique_ptr<_StupidRenderComponent<RenderFunc>>
makeStupidRenderComponent(Test::StupidRenderer* pTargetStructure,
                          RenderFunc rfunc){
    return make_unique<_StupidRenderComponent<RenderFunc>>(pTargetStructure, std::move(rfunc));
}

//StupidCameraComponent
class StupidCameraComponent : public Component{
public:
    StupidCameraComponent(Test::StupidRenderer* pTargetStructure,
                          glm::mat4& view,
                          glm::mat4& proj) :
        pTargetStructure(pTargetStructure),
        view(view),
        proj(proj)
        {}
    virtual ~StupidCameraComponent(void){}

    const glm::mat4& getViewMatrix(void){
        return view;
    }
    const glm::mat4& getProjMatrix(void){
        return proj;
    }
protected:
    Test::StupidRenderer* pTargetStructure;
    glm::mat4& view;
    glm::mat4& proj;

    /* NEVER OVERRIDE! */
    void addToStructure(void);
    void removeFromStructure(void);
};

//LogicComponent
class LogicComponent : public Component{
public:
    LogicComponent(void){}
    virtual ~LogicComponent(void){}

    virtual void logic(void) = 0;

    LogicComponent(const LogicComponent&) = delete;
    LogicComponent& operator=(const LogicComponent&) = delete;
protected:
    /* NEVER OVERRIDE! */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename LogicFunc>
class _LogicComponent : public LogicComponent{
public:
    _LogicComponent(LogicFunc _lfunc) :
        lfunc(std::move(_lfunc))
        {}

    void logic(void){
        lfunc();
    }
private:
    LogicFunc lfunc;
};
template<typename LogicFunc>
std::unique_ptr<_LogicComponent<LogicFunc>>
makeLogicComponent(LogicFunc lfunc){
    return make_unique<_LogicComponent<LogicFunc>>(std::move(lfunc));
}

//PhysicsComponent
class PhysicsComponent : public Component{
public:
    PhysicsComponent(std::unique_ptr<btCollisionShape> pCollisionMesh,
                     PhysicsNode* pParent,
                     glm::vec3 initialVel,
                     glm::mat4& model,
                     glm::mat4& scale,
                     float mass,
                     float restitution);
    virtual ~PhysicsComponent(void);
    PhysicsComponent(const PhysicsComponent&) = delete;
    PhysicsComponent& operator=(const PhysicsComponent&) = delete;

    const glm::mat4& getModelMatrix(void);
    void setModelMatrix(const glm::mat4&);

    const glm::mat4& getScaleMatrix(void);
protected:
    std::unique_ptr<btCollisionShape> pCollisionMesh; //TODO: make this a resource
    PhysicsNode* pParent;
    std::unique_ptr<PhysicsNode> pPhysicsNode;
    glm::mat4& model;
    glm::mat4& scale;
    float mass;
    float restitution;
    PhysicsMotionState motionState;
    std::unique_ptr<btRigidBody> pPhysicsBody;

    /* NEVER OVERRIDE! */
    void addToStructure(void);
    void removeFromStructure(void);
};


#endif // COMPONENT_HH
