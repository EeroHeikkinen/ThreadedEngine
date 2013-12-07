#ifndef COMPONENT_HH
#define COMPONENT_HH

#include "physics_motion_state.hh"

#include <mutex>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class PhysicsNode;


class RenderComponent{
public:
    RenderComponent(void);
    virtual ~RenderComponent(void);

    virtual void render(const glm::mat4&, const glm::mat4&) = 0;

    RenderComponent(const RenderComponent&) = delete;
    RenderComponent& operator=(const RenderComponent&) = delete;
};


class LogicComponent{
public:
    LogicComponent(void);
    virtual ~LogicComponent(void);

    virtual void logic(void) = 0;

    LogicComponent(const LogicComponent&) = delete;
    LogicComponent& operator=(const LogicComponent&) = delete;
};


class PhysicsComponent{
public:
    PhysicsComponent(btCollisionShape* collisionMesh_,
                     PhysicsNode* parent_,
                     glm::vec3 initialPos_,
                     glm::vec3 initialVel_,
                     glm::mat4& model_,
                     float mass_,
                     float restitution_);
    virtual ~PhysicsComponent(void);

    void setTransformation(const btTransform& worldTrans);

    PhysicsComponent(const PhysicsComponent&) = delete;
    PhysicsComponent& operator=(const PhysicsComponent&) = delete;
protected:
    btCollisionShape* collisionMesh;
    PhysicsMotionState* motionState;
    PhysicsNode* node;
    glm::vec3 initialPos;
    glm::mat4& model;
    float mass;
    btRigidBody* physicsBody;
};


#endif // COMPONENT_HH
