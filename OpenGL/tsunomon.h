#ifndef TSUNOMON_H_
#define TSUNOMON_H_

#include "monsters.h"

class Tsunomon : public Monster {
public:
    Tsunomon(modelImporter* importer, Physics* phys) : Monster("resources/tsunomon/tsunomon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.002)) {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
