#ifndef BLACKAQUMON_H_
#define BLACKAQUMON_H_

#include "monsters.h"

class BlackAqumon : public Monster {
public:
    BlackAqumon(modelImporter* importer, Physics* phys) : Monster("resources/blackaqumon/blackAqumon.obj", importer, phys) {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
