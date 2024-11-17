#ifndef AQUILAMON_H_
#define AQUILAMON_H_

#include "monsters.h"

class Aquilamon : public Monster {
public:
    Aquilamon(modelImporter* importer, Physics* phys) : Monster("resources/aquilamon/aquilamon.obj", importer, phys) {
        double scale = 0.15;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
