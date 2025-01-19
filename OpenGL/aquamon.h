#ifndef AQUAMON_H_
#define AQUAMON_H_

#include "monsters.h"

class Aquamon : public Monster 
{
private:
    int damage; // Ilość zadawanych obrażeń

public:
    Aquamon(modelImporter* importer, Physics* phys, int dmg = 12) // Domyślna wartość obrażeń to 12
        : Monster("resources/agumon/agumon.obj", importer, phys, glm::vec3(0.003, 0.01, 0.001)), damage(dmg) 
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
