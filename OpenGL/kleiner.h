#ifndef KLEINER_H_
#define KLEINER_H_

#include "monsters.h"

class Kleiner : public Monster {
public:
    Kleiner(modelImporter* importer, Physics* phys) : Monster("resources/kleiner/kleiner.obj", importer, phys) {
        double scale = 0.09;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
