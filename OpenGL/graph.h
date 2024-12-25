#ifndef GRAPH_H_

#define GRAPH_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>

// To nie jest graf, ale na poczatku to mial byc graf wiec nazwy zostaly

class NodeMap
{
public:
	std::pair <int, int> position;
	std::vector <NodeMap*> children;
	NodeMap* parent;
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
		this->parent = parent;
		this->whereParent = whereParent;
	}

};
class GraphMap
{
public:
	int size = 1;
	std::map<std::pair <int, int>, NodeMap*> map;
	int mainIters = 0;
	int maxRooms = 35;
	int iters = 0;
	int max = 5;
	int dimensions[4] = { 0,0,0,0 };
	GraphMap()
	{
		std::srand(time(NULL));
		std::pair <int, int> pair = std::make_pair(0, 0);
		map[pair] = new NodeMap(pair);
		
		branchNode(map[pair], 4);
		//showGraphStructure();
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
						if (maxRooms > 0)
						{
							maxRooms--;
							this->size++;
							branchNode(map[newPos], 3);
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
					if (map[pos]->whereParent == 3 || map[pos]->directions[3] != -1)
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
					if (map[pos]->whereParent == 1 || map[pos]->directions[1] != -1)
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
