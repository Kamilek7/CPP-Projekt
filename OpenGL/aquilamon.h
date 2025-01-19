#ifndef AQUILAMON_H_
#define AQUILAMON_H_

#include "monsters.h"

class Aquilamon : public Monster {
private:
    int damage; // Ilość zadawanych obrażeń

public:
    Aquilamon(modelImporter* importer, Physics* phys, int dmg = 15) // Domyślna wartość obrażeń to 15
        : Monster("resources/aquilamon/aquilamon.obj", importer, phys, glm::vec3(0.001, 0.1, 0.001)), damage(dmg) {
        double scale = 0.15;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    int getDamage() const {
        return damage;
    }

};

#endif
