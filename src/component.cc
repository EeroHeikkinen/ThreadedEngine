#include "component.hh"
#include "device.hh"

#include <iostream>//TEMP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;


//RenderComponent

RenderComponent::RenderComponent(void){
    //add the component to the render thread
    Device::getDevice().getSceneGraph().addRenderComponent(this);
}

RenderComponent::~RenderComponent(void){
    //delete the component from the render thread
    Device::getDevice().getSceneGraph().deleteRenderComponent(this);
}

//PhysicsComponent

PhysicsComponent::PhysicsComponent(btCollisionShape* collisionMesh_,
                                   PhysicsNode* parent_,
								   vec3 initialPos_,
								   vec3 initialVel_,
								   mat4& model_,
								   float mass_,
								   float restitution_) :
    collisionMesh(collisionMesh_),
    initialPos(initialPos_),
    model(model_),
    mass(mass_)
    {
        node = Device::getDevice().getPhysicsThread().getPhysicsTree().addNode(parent_, this);

        btTransform tmp_btInitialPos(btQuaternion(0,0,0,1),
                                     btVector3(initialPos.x, initialPos.y, initialPos.z));

    	// btMatrix3x3 B = tmp_btInitialPos.getBasis();
        // btVector3 O = tmp_btInitialPos.getOrigin();
        // std::cout << "InitialBasis: " << std::endl;
        // for(size_t i = 0; i < 3; ++i){
        //     for(size_t j = 0; j < 3; ++j)
        //         std::cout << B[i][j] << " ";
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;
        // std::cout << "InitialOrigin: ";
        // for(size_t i = 0; i < 3; ++i)
        //     std::cout << O[i] << " ";
        // std::cout << std::endl << std::endl;

        motionState = new PhysicsMotionState(tmp_btInitialPos, this);

        // WUT IS THIS FALLINERTIA
        btVector3 fallInertia = btVector3(0.0,0.0,0.0);
        collisionMesh->calculateLocalInertia(btScalar(mass), fallInertia);
        std::cout << "Inertia: " << fallInertia.x() << " " << fallInertia.y() << " " << fallInertia.z() << std::endl;
        btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, motionState,
                                                                 collisionMesh, fallInertia);
        physicsBody = new btRigidBody(RigidBodyCI);

        physicsBody->setRestitution(restitution_);
        //physicsBody->setLinearVelocity(btVector3(initialVel_.x, initialVel_.y, initialVel_.z));
        Device::getDevice().getPhysicsThread().getDynamicsWorld().addRigidBody(physicsBody);
    }

PhysicsComponent::~PhysicsComponent(){
	delete node;
	Device::getDevice().getPhysicsThread().getDynamicsWorld().removeRigidBody(physicsBody);
	delete collisionMesh;
	delete physicsBody;
	delete motionState;
}

void PhysicsComponent::setTransformation(const btTransform& worldTrans){
	btQuaternion rot = worldTrans.getRotation();
	btVector3 pos = worldTrans.getOrigin();
	quat glm_rot = quat(rot.w(), rot.x(), rot.y(), rot.z());
	model = translate(pos.x(), pos.y(), pos.z()) * toMat4(glm_rot);

    //std::cout << pos.x() << std::endl << pos.y() << std::endl << pos.z() << std::endl << std::endl;
}

//LogicComponent

LogicComponent::LogicComponent(void) {
    //add the component to the logic thread
    Device::getDevice().getLogicThread().addLogicComponent(this);
}

LogicComponent::~LogicComponent(void) {
    //delete the component from the logic thread
    Device::getDevice().getLogicThread().deleteLogicComponent(this);
}
