#ifndef COMPONENT_HH
#define COMPONENT_HH

#include "physics_utils.hh"
#include "make_unique.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicsNode;
namespace Test{class StupidRenderer;}


class Component{
public:
    Component(){}
    virtual ~Component(){}
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
    _StupidRenderComponent(Test::StupidRenderer* pTargetStructure,
                           RenderFunc rfunc) :
        StupidRenderComponent(pTargetStructure),
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
makeStupidRenderComponent(Test::StupidRenderer* pTargetStructure,
                          RenderFunc rfunc){
    return make_unique<_StupidRenderComponent<RenderFunc>>(pTargetStructure, rfunc);
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
    /* For successful threading, these two      *
     * functions shall be called in the most    *
     * derived class constructor and destructor *
     * and NEVER OVERRIDDEN!                    */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename... Args>
class _StupidCameraComponent : public StupidCameraComponent{
public:
    _StupidCameraComponent(Args&&... args) :
        StupidCameraComponent(std::forward<Args>(args)...)
        {
            addToStructure();
        }
    ~_StupidCameraComponent(void){
        removeFromStructure();
    }
};
template<typename... Args>
std::unique_ptr<_StupidCameraComponent<Args...>>
makeStupidCameraComponent(Args&&... args){
    return make_unique<_StupidCameraComponent<Args...>>(std::forward<Args>(args)...);
}

//LogicComponent
class LogicComponent : public Component{
public:
    LogicComponent(void){}
    virtual ~LogicComponent(void){}

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
    PhysicsNode* pParent;
    std::unique_ptr<PhysicsMotionState> pMotionState;
    std::unique_ptr<PhysicsNode> pPhysicsNode;
    glm::vec3 initialPos;
    glm::vec3 initialVel;
    glm::mat4& model;
    float mass;
    float restitution;
    std::unique_ptr<btRigidBody> pPhysicsBody;

    /* For successful threading, these two      *
     * functions shall be called in the most    *
     * derived class constructor and destructor *
     * and NEVER OVERRIDDEN!                    */
    void addToStructure(void);
    void removeFromStructure(void);
};
template<typename... Args>
class _PhysicsComponent : public PhysicsComponent{
public:
    _PhysicsComponent(Args&&... args) :
        PhysicsComponent(std::forward<Args>(args)...)
        {
            addToStructure();
        }
    ~_PhysicsComponent(void){
        removeFromStructure();
    }
};
template<typename... Args>
std::unique_ptr<_PhysicsComponent<Args...>>
makePhysicsComponent(Args&&... args){
    return make_unique<_PhysicsComponent<Args...>>(std::forward<Args>(args)...);
}

#endif // COMPONENT_HH
