#ifndef COLLISION_LISTENER_H_

#define COLLISION_LISTENER_H_

#include "physicsObject.h"

class MyCollisionListener : public EventListener {

    std::vector <ingameObject*>* objectsPtr;
public:
    virtual void onContact(const CollisionCallback::CallbackData& callbackData) override {

        for (uint p = 0; p < callbackData.getNbContactPairs(); p++) {

            CollisionCallback::ContactPair contactPair = callbackData.getContactPair(p);
            Body* bd1 =  contactPair.getBody1();
            Body* bd2 = contactPair.getBody2();
            ((physicsObject*)(bd1->getUserData()))->collidedWith(bd2);
            ((physicsObject*)(bd2->getUserData()))->collidedWith(bd1);
        }
    }
    void init(std::vector <ingameObject*>* objects)
    {
        this->objectsPtr = objects;
    }

};
#endif