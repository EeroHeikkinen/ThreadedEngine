#ifndef PHYSICS_UTILS_HH
#define PHYSICS_UTILS_HH

#include <LinearMath/btMotionState.h>
#include <btBulletDynamicsCommon.h>
#include <mutex>
#include <iostream>

class PhysicsComponent;


class PhysicsMotionState : public btMotionState{
public:
	PhysicsMotionState(PhysicsComponent* pComponent);
	virtual ~PhysicsMotionState() {}

	void setComponent(PhysicsComponent* pComponent);

	virtual void getWorldTransform(btTransform& worldTrans) const;
	virtual void setWorldTransform(const btTransform& worldTrans);
private:
	PhysicsComponent* pComponent;
};

//DiscreteDynamicsWorld mutexed wrapper
class DiscreteDynamicsWorld : public btDiscreteDynamicsWorld{
public:
    template<typename... Args>
    DiscreteDynamicsWorld(Args&&... args) :
        btDiscreteDynamicsWorld(std::forward<Args>(args)...)
        {}

    template<typename... Args>
    int stepSimulation(Args&&... args){
        std::lock_guard<std::mutex> lock(mutex);
        return btDiscreteDynamicsWorld::stepSimulation(std::forward<Args>(args)...);
    }

    virtual void removeRigidBody(btRigidBody* pRigidBody){
        std::lock_guard<std::mutex> lock(mutex);
        btDiscreteDynamicsWorld::removeRigidBody(pRigidBody);
    }
    virtual void addRigidBody(btRigidBody* pRigidBody){
        std::lock_guard<std::mutex> lock(mutex);
        btDiscreteDynamicsWorld::addRigidBody(pRigidBody);
    }
private:
    std::mutex mutex;
};


#endif //PHYS_MOTION_STATE_HH
