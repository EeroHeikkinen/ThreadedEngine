#ifndef PHYS_MOTION_STATE_HH
#define PHYS_MOTION_STATE_HH

#include <LinearMath/btMotionState.h>
#include <btBulletDynamicsCommon.h>

class PhysicsNode;
class PhysicsComponent;


class PhysicsMotionState : public btMotionState{
public:
	PhysicsMotionState(const btTransform& initialPos_,  PhysicsComponent* component_);
	virtual ~PhysicsMotionState() {}

	void setComponent(PhysicsComponent* component_);

	virtual void getWorldTransform(btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans);
private:
	btTransform initialPos;
	PhysicsComponent* component;
};


#endif //PHYS_MOTION_STATE_HH
