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
        std::pair<double, double> thisPosD = getGraphPosFromCoords(this->model.translation);

        std::pair<int, int> thisPos = getMyGraphPosFromDoubles(thisPosD);
        if (thisPos.first == -420 || thisPos.second == -420)
            thisPos = this->rememberedMyPos;
        std::pair<int, int> playerPos = getPlayerGraphPosFromCoords(*this->playerPos);

        if ((thisPos != this->rememberedMyPos || playerPos != this->rememberedPlayerPos) && (thisPos!=playerPos))
        {
            this->rememberedMyPos = thisPos;
            this->rememberedPlayerPos = playerPos;
            std::vector <NodeMap*> path = this->map.getShortestPath(playerPos, thisPos);
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
    std::pair<int, int> getMyGraphPosFromDoubles(std::pair<double, double> thisPosD)
    {
        int x, y;
        if (abs(thisPosD.first - floor(thisPosD.first + 0.5)) <= 0.1)
            x = floor(thisPosD.first + 0.5);
        else
            x = -420;

        if (abs(thisPosD.second - floor(thisPosD.second + 0.5)) <= 0.1)
            y = floor(thisPosD.second + 0.5);
        else
            y = -420;
        return std::make_pair(x, y);
    }
    std::pair<double, double> getGraphPosFromCoords(glm::vec3 coords)
    {
        double xD = coords.x / 2 / mapSize.x;
        double yD = coords.z / 2 / mapSize.z;
        return std::make_pair(xD, yD);
    }

    std::pair<int, int> getPlayerGraphPosFromCoords(glm::vec3 coords)
    {
        double xD = coords.x / 2 / mapSize.x;
        double yD = coords.z / 2 / mapSize.z;

        int x = floor(xD + 0.5);
        int y = floor(yD + 0.5);
        return std::make_pair(x, y);
    }
    glm::vec3 mapSize;
    GraphMap map;
public:
    Tsunomon(modelImporter* importer, Physics* phys, glm::vec3 mapsize, GraphMap map) : Monster("resources/tsunomon/tsunomon.obj", importer, phys, glm::vec3(0.01, 0.1, 0.002)) {
        this->mapSize = mapsize;
        double scale = 0.1;
        this->model.scale = glm::vec3(scale, scale, scale);
        this->map = map;
    }

};

#endif
