#ifndef TENEMON_H_
#define TENEMON_H_

#include "monsters.h"

class Tenemon : public Monster {

private:
    int damage; // Ilość zadawanych obrażeń

public:
    Tenemon(modelImporter* importer, Physics* phys, int dmg = 10) 
        : Monster("resources/tanemon/tanemon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.005))
    {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    int getDamage() const
    {
        return damage;
    }
};

#endif
