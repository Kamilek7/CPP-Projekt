#ifndef GRAPH_H_

#define GRAPH_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

class NodeMap
{
public:
	bool visitedByPlayer = false;
	std::pair <int, int> position;
	std::vector <NodeMap*> children;
	int directions[4] = { -1,-1,-1,-1 };
	int whereParent = -1;
	NodeMap(std::pair <int, int> pos)
	{
		this->position = pos;
	}
	void addChildNode(NodeMap* child, int direction) {
		this->children.push_back(child);
		this->directions[direction] = this->children.size() - 1;
	}
	void addParentNode(NodeMap* parent, int whereParent)
	{
		this->whereParent = whereParent;
		this->children.push_back(parent);
		this->directions[whereParent] = this->children.size() - 1;
	}

};
class GraphMap
{
public:
	std::map<std::pair <int, int>, NodeMap*> map;
	int mainIters = 0;
	int maxRooms = 35;
	int iters = 0;
	int max = 5;
	int dimensions[4] = { 0,0,0,0 };

	std::vector<NodeMap*> edges = {};

	GraphMap()
	{
		std::srand(time(NULL));
		std::pair <int, int> pair = std::make_pair(0, 0);
		map[pair] = new NodeMap(pair);
		
		branchNode(map[pair], 4);
		//showGraphStructure();
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i]->children.size() > 1)
			{
				edges.erase(edges.begin() + i);
				i--;
			}
		}
	 }

	void branchNode(NodeMap* node, int numAvDirections)
	{
		
		int directionNum = std::rand() % numAvDirections + 1;

		// 0 -> North
		// 1 -> South
		// 2 -> East
		// 3 -> West
		if (mainIters < 7)
		{
			if (iters < max)
			{
				std::vector <int> directionsToPick = { 0,1,2,3 };
				int directions = 4;
				if (node->whereParent != -1)
				{
					directionsToPick.erase(directionsToPick.begin() + node->whereParent);
					directions = 3;
				}
					
				std::vector <int> picked = {};

				for (int i = 0; i < directionNum; i++)
				{
					int picker = std::rand() % (directions - i);



					int pick = (directionsToPick[picker]);
					std::pair <int, int> newPos = getNewPosition(node->position, pick);
					int parentPos = getOppositeDirection(pick);
					if (map.find(newPos) == map.end()) {

						if (newPos.first < dimensions[0])
							dimensions[0] = newPos.first;
						if (newPos.first > dimensions[1])
							dimensions[1] = newPos.first;
						if (newPos.second < dimensions[2])
							dimensions[2] = newPos.second;
						if (newPos.second > dimensions[3])
							dimensions[3] = newPos.second;

						map[newPos] = new NodeMap(newPos);

						map[newPos]->addParentNode(node, parentPos);
						node->addChildNode(map[newPos], pick);

						
						iters++;
						maxRooms--;
						if (maxRooms > 0)
						{
							branchNode(map[newPos], 3);
						}
						else
						{
							edges.push_back(map[newPos]);
						}
							
						

					}
					else
					{
						map[newPos]->addChildNode(node, parentPos);
						node->addChildNode(map[newPos], pick);
					}

					directionsToPick.erase(directionsToPick.begin() + picker);

				}
			}
			else
			{
				mainIters++;
				iters = 0;
				max = std::rand() % 9 + 3;
			}
		}
	}
	std::vector<NodeMap*> getShortestPath(std::pair <int, int> start, std::pair <int, int> end)
	{
		std::map<NodeMap*, NodeMap*> parent;
		std::map<NodeMap*, bool> visited;
		std::queue<NodeMap*> Q;
		visited[map[start]] = true;
		Q.push(map[start]);
		while (!Q.empty()) {

			NodeMap* curr = Q.front();
			Q.pop();
			for (int i = 0; i < curr->children.size(); i++) {
				if (!visited[curr->children[i]]) {
					visited[curr->children[i]] = true;
					Q.push(curr->children[i]);
					parent[curr->children[i]] = curr;
				}
			}
		}
		std::vector<NodeMap*> A = {};
		NodeMap* node = map[end];
		while (node->position != start)
		{
			A.push_back(node);
			node = parent[node];
		}

		node = nullptr;
		delete node;

		return A;

	}
	std::pair<int, int> getCenteredGraphPosFromDoubles(std::pair<double, double> thisPosD)
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
	std::pair<double, double> getDblCenteredPosFromCoords(glm::vec3 coords, glm::vec3 mapSize)
	{
		double xD = coords.x / 2 / mapSize.x;
		double yD = coords.z / 2 / mapSize.z;
		return std::make_pair(xD, yD);
	}

	std::pair<int, int> getAbsoluteGraphPosFromCoords(glm::vec3 coords, glm::vec3 mapSize)
	{
		double xD = coords.x / 2 / mapSize.x;
		double yD = coords.z / 2 / mapSize.z;

		int x = floor(xD + 0.5);
		int y = floor(yD + 0.5);
		return std::make_pair(x, y);
	}

private:
	int getOppositeDirection(int direction)
	{
		return (abs(direction - 1)) % 2 + 2 * (int)(direction / 2);
	}
	std::pair <int, int> getNewPosition(std::pair<int, int> parentPos, int direction)
	{
		return std::make_pair(parentPos.first + ((int(direction / 2)) * (5 - 2 * direction)), parentPos.second +((int(abs(direction - 3) / 2)) * (1 - 2 * direction)));
	}
	void showGraphStructure()
	{
		std::cout << "Graph Dimensions: " << dimensions[1] - dimensions[0] << " by " << dimensions[3] - dimensions[2] << ". (width, height)" << std::endl<<std::endl;
		for (int y = dimensions[3]; y >= dimensions[2]; y--)
		{
			for (int x = dimensions[0]; x <= dimensions[1]; x++)
			{
				
				std::pair <int, int> pos = std::make_pair(x, y);
				if (map.find(pos) != map.end())
				{
					if (map[pos]->directions[3] != -1)
						std::cout << "-";
					else
						std::cout << " ";
					std::cout << "x";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
			for (int x = dimensions[0]; x <= dimensions[1]; x++)
			{
				std::pair <int, int> pos = std::make_pair(x, y);
				if (map.find(pos) != map.end())
				{
					std::cout << " ";
					if (map[pos]->directions[1] != -1)
						std::cout << "|";
					else
						std::cout << " ";
					
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;

	}


};



#endif