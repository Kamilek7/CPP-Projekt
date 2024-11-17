#ifndef TSUNOMON_H_
#define TSUNOMON_H_

#include "monsters.h"

class Tsunomon : public Monster {
public:
    Tsunomon(modelImporter* importer, Physics* phys) : Monster("resources/tsunomon/tsunomon.obj", importer, phys) {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
