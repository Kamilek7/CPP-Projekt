#ifndef DARKTYRANNOMON_H_
#define DARKTYRANNOMON_H_

#include "monsters.h"

class DarkTyrannomon : public Monster {

private:
    int damage; // Ilość zadawanych obrażeń

public:
    DarkTyrannomon(modelImporter* importer, Physics* phys, int dmg = 10) 
        : Monster("resources/darktyrannomon/darkTyrannomon.obj", importer, phys, glm::vec3(0.05, 0.3, 0.001)) {
        double scale = 0.18;
        this->model.scale = glm::vec3(scale, scale, scale);
    }

    int getDamage() const
    {
        return damage;
    }
};

#endif
