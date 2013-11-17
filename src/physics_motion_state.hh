#ifndef PHYS_MOTION_STATE_HH
#define PHYS_MOTION_STATE_HH

#include <LinearMath/btMotionState.h>
#include <btBulletDynamicsCommon.h>
class PhysicsNode;


class PhysicsMotionState : public btMotionState{
public:
	PhysicsMotionState(const btTransform& initialPos_,  PhysicsNode* node_);
	virtual ~PhysicsMotionState() {}

	void setNode(PhysicsNode* node_);

	virtual void getWorldTransform(btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans);
private:
	btTransform initialPos;
	PhysicsNode* node;
};


#endif //PHYS_MOTION_STATE_HH
