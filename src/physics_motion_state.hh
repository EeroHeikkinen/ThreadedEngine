#ifndef PHYS_MOTION_STATE_HH
#define PHYS_MOTION_STATE_HH

#include <LinearMath/btMotionState.h>
#include <btBulletDynamicsCommon.h>

class PhysicsComponent;


class PhysicsMotionState : public btMotionState{
public:
	PhysicsMotionState(const btTransform& initialPos,  PhysicsComponent* pComponent);
	virtual ~PhysicsMotionState() {}

	void setComponent(PhysicsComponent* pComponent);

	virtual void getWorldTransform(btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans);
private:
	btTransform initialPos;
	PhysicsComponent* pComponent;
};


#endif //PHYS_MOTION_STATE_HH
