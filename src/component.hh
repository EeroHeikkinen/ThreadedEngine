#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <glm/glm.hpp>

#include "physics_motion_state.hh"

class PhysicsNode;

#include <glm/gtc/matrix_transform.hpp>


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
    PhysicsComponent(btCollisionShape* collisionMesh_, PhysicsNode* parent, glm::vec3 pos, float mass_);

    PhysicsComponent(const PhysicsComponent&) = delete;
    virtual ~PhysicsComponent(void);

    void setTransformation(const btTransform& worldTrans);

    PhysicsComponent& operator=(const PhysicsComponent&) = delete;

private:
    btCollisionShape* collisionMesh;
    PhysicsMotionState* motionState;
    PhysicsNode* node;
    glm::vec3 initial_pos;
    glm::mat4 to_world;
    float mass;
    btRigidBody* physicsBody;

};


#endif // COMPONENT_HH
