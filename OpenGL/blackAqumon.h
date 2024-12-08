#ifndef BLACKAQUMON_H_
#define BLACKAQUMON_H_

#include "monsters.h"

class BlackAqumon : public Monster {
public:
    BlackAqumon(modelImporter* importer, Physics* phys) : Monster("resources/blackAgumon/blackAgumon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.005)) {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
