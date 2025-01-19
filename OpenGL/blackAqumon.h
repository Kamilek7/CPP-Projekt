#ifndef BLACKAQUMON_H_
#define BLACKAQUMON_H_

#include "monsters.h"

class BlackAqumon : public Monster {
private:
    int damage; // Ilość zadawanych obrażeń

public:
    BlackAqumon(modelImporter* importer, Physics* phys, int dmg = 20) // Domyślna wartość obrażeń to 20
        : Monster("resources/blackAgumon/blackAgumon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.005)), damage(dmg) {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    int getDamage() const {
        return damage;
    }

};

#endif
