#ifndef COMPONENT_HH
#define COMPONENT_HH


#include "physics_motion_state.hh"

#include <mutex>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class PhysicsNode;


class RenderComponent {
public:
    RenderComponent(void);
    RenderComponent(const RenderComponent&) = delete;
    virtual ~RenderComponent(void);

    virtual void render(const glm::mat4&, const glm::mat4&) = 0;

    RenderComponent& operator=(const RenderComponent&) = delete;
};



class LogicComponent {
public:
    LogicComponent(void);
    LogicComponent(const LogicComponent&) = delete;
    virtual ~LogicComponent(void);

    virtual void logic(void) = 0;

    LogicComponent& operator=(const LogicComponent&) = delete;
};


class PhysicsComponent {
public:
    PhysicsComponent(
                     btCollisionShape* collisionMesh_,
                     PhysicsNode* parent,
                     glm::vec3 pos,
                     glm::mat4& model,
                     float mass_
                     );

    PhysicsComponent(const PhysicsComponent&) = delete;
    virtual ~PhysicsComponent(void);

    void setTransformation(const btTransform& worldTrans);

    PhysicsComponent& operator=(const PhysicsComponent&) = delete;

protected:
    btCollisionShape* collisionMesh;
    PhysicsMotionState* motionState;
    PhysicsNode* node;
    glm::vec3 initial_pos;
    glm::mat4& model;
    float mass;
    btRigidBody* physicsBody;
};


#endif // COMPONENT_HH
