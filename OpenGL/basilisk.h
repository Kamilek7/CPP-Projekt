#ifndef BASILISK_H_
#define BASILISK_H_

#include "monsters.h"

class Basilisk : public Monster
{
private:
    int damage; // Ilość zadawanych obrażeń

public:
    Basilisk(modelImporter* importer, Physics* phys, int dmg = 10) // Domyślna wartość obrażeń to 10
        : Monster("resources/basilisk/c3270.obj", importer, phys, glm::vec3(0.1, 0.4, 0.5)), damage(dmg)
    {
        double scale = 0.5;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    int getDamage() const
    {
        return damage;
    }

};

#endif
