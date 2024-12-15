#ifndef MONSTERS_H_
#define MONSTERS_H_

#include "npc.h"
#include <chrono>

class Monster : public NPC
{
private:
    int lives; // Liczba żyć potwora
    std::chrono::steady_clock::time_point lastDamageTime;
    std::chrono::steady_clock::time_point lastJumpTime;   

public:
    Monster(const char* name, modelImporter* importer, Physics* phys, glm::vec3 size) 
        : NPC(name, importer, phys, size), lives(2), lastDamageTime(std::chrono::steady_clock::now())
    {
        double scale = 0.005;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    void collidedWith(Body* bd)
    {
        std::vector<physicsObject*> test = *(std::vector<physicsObject*>*)(bd->getUserData());
        ((*(std::vector<physicsObject*>*)(bd->getUserData()))[0])->collidedWithMonster();
    }

    void collidedWithPlayer()
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastDamageTime).count() >= 3)
        {
            lastDamageTime = currentTime;
            if (--lives <= 0)
            {
                this->dead = true;
            }
        }
    }

    void process(float dt)
    {
        auto currentTime = std::chrono::steady_clock::now();
        
        const double jumpInterval = 3.0; 
        const Vector3 jumpForce(0, 1.0, 0); 

        // Automatyczny skok co 3 sekundy
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastJumpTime).count() >= jumpInterval)
        {
            if (this->body->getLinearVelocity().y <= 0.1) 
            {
                this->body->applyLocalForceAtCenterOfMass(jumpForce);
                lastJumpTime = currentTime; 
            }
        }
    }

    int getLives() const
    {
        return lives;
    }
};

#endif
