#ifndef BARTEK_H_
#define BARTEK_H_

#include "monsters.h"

class Bartek : public Monster {
public:
    Bartek(modelImporter* importer, Physics* phys) : Monster("resources/bartek/bartek.obj", importer, phys) {
        double scale = 0.12;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
