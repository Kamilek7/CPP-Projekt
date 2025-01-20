#ifndef TSUNOMON_H_
#define TSUNOMON_H_

#include "monsters.h"
#include "graph.h"

class Tsunomon : public Monster {

protected:
    std::pair<int, int> rememberedPlayerPos = std::make_pair(0,0);
    std::pair<int, int> rememberedMyPos = std::make_pair(0, 0);
    std::pair <int,int> rememberedNextLoc = std::make_pair(0, 0);
    void additionalMovement(float dt)
    {
        if (glm::length(*this->playerPos - this->model.translation) >= 5)
            this->followPlayerInGraph();
    }
    void followPlayerInGraph()
    {
        std::pair<double, double> thisPosD = map->getDblCenteredPosFromCoords(this->model.translation, mapSize);

        std::pair<int, int> thisPos = map->getCenteredGraphPosFromDoubles(thisPosD);
        if (thisPos.first == -420 || thisPos.second == -420)
            thisPos = this->rememberedMyPos;
        std::pair<int, int> playerPos = this->map->getAbsoluteGraphPosFromCoords(*this->playerPos, mapSize);
        this->map->map[playerPos]->visitedByPlayer = true;
        if ((thisPos != this->rememberedMyPos || playerPos != this->rememberedPlayerPos) && (thisPos!=playerPos))
        {
            this->rememberedMyPos = thisPos;
            this->rememberedPlayerPos = playerPos;
            std::vector <NodeMap*> path = this->map->getShortestPath(playerPos, thisPos);
            if (path.size() > 1)
            {
                if (this->rememberedNextLoc != path[0]->position && this->rememberedNextLoc != std::make_pair(0, 0))
                    this->rememberedNextLoc = path[0]->position;
                else
                {
                    this->rememberedNextLoc = path[1]->position;
                    this->body->setLinearVelocity(Vector3(0,0,0));
                }
                    
            }
            else
                this->rememberedNextLoc = playerPos;

        }
        Vector3 movementDirection;
        movementDirection.x = rememberedNextLoc.first - thisPos.first;
        movementDirection.z = rememberedNextLoc.second - thisPos.second;
        movementDirection *= 10;
        this->body->applyLocalForceAtCenterOfMass(movementDirection);

    }

    glm::vec3 mapSize;
    GraphMap* map;
public:
    Tsunomon(modelImporter* importer, Physics* phys, glm::vec3 mapsize, GraphMap* map) : Monster("resources/tsunomon/tsunomon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.002)) {
        this->mapSize = mapsize;
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
        this->map = map;
        this->damage = 15;
    }

};

#endif