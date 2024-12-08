#ifndef AQUAMON_H_

#define AQUAMON_H_

#include "monsters.h"

class Aquamon :public Monster 
{
public:
    Aquamon(modelImporter* importer, Physics* phys) : Monster("resources/agumon/agumon.obj", importer, phys, glm::vec3(0.003, 0.01, 0.001))
    {
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
    }
};

#endif
