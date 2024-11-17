#ifndef DARKTYRANNOMON_H_
#define DARKTYRANNOMON_H_

#include "monsters.h"

class DarkTyrannomon : public Monster {
public:
    DarkTyrannomon(modelImporter* importer, Physics* phys) : Monster("resources/darktyrannomon/darkTyrannomon.obj", importer, phys) {
        double scale = 0.18;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
