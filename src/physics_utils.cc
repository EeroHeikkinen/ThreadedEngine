#include "physics_utils.hh"
#include "component.hh"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>


PhysicsMotionState::PhysicsMotionState(PhysicsComponent* pComponent) :
    pComponent(pComponent)
    {}

void PhysicsMotionState::setComponent(PhysicsComponent* _pComponent){
	pComponent = _pComponent;
}

void PhysicsMotionState::getWorldTransform(btTransform& worldTrans) const{
    const glm::mat4& model = pComponent->getModelMatrix();

    glm::vec3 trans(model[3]);
    btVector3 btTrans(model[3][0], model[3][1], model[3][2]);

    glm::quat rot(glm::toQuat(model));
    btQuaternion btRot(rot.x, rot.y, rot.z, rot.w);

    worldTrans.setOrigin(btTrans);
    worldTrans.setRotation(btRot);
}

void PhysicsMotionState::setWorldTransform(const btTransform& worldTrans){
    btQuaternion btRot(worldTrans.getRotation());
    glm::quat quatRot(btRot.w(), btRot.x(), btRot.y(), btRot.z());
    glm::mat4 rot(glm::toMat4(quatRot));

    btVector3 btTrans = worldTrans.getOrigin();
    glm::mat4 trans = glm::translate(btTrans.x(), btTrans.y(), btTrans.z());

    const glm::mat4& scale = pComponent->getScaleMatrix();

	pComponent->setModelMatrix(trans * rot * scale);
}
