#ifndef COLLIDERCUBE_H_
#define COLLIDERCUBE_H_

#include "monsters.h"

class ColliderCube : public Monster {
public:
    ColliderCube(modelImporter* importer, Physics* phys) : Monster("resources/collidercube/colliderCube.obj", importer, phys) {
        double scale = 0.2;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
