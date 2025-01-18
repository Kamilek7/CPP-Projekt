#ifndef ANIMA_H_

#define ANIMA_H_

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>


struct Scales
{
	float t;
	glm::vec3 scale;
};

struct Rotations
{
	float t;
	aiQuaternion rotation;
};

struct Translations
{
	float t;
	glm::vec3 translation;
};

struct AnimationPacket
{
	std::vector <Translations> t;
	std::vector <Scales> s;
	std::vector <Rotations> r;

};

class Animation
{

	bool empty;
	bool corrupted;

	bool looped;
	float currentTime;
	std::map <int, AnimationPacket> animationPackets;

public:
	float duration;
	float ticksPerSecond;
	std::string name;
	Animation()
	{
		corrupted = false;
		empty = true;
		currentTime = 0;
	}

	void markAsCorrupted()
	{
		this->corrupted = true;
	}

	void passAnimationInfo(float ticksPerSecond, std::map <int, AnimationPacket> packet, float duration)
	{
		this->ticksPerSecond = ticksPerSecond;
		this->animationPackets = packet;
		this->duration = duration;
	}


	void setUp(bool loop)
	{
		this->looped = loop;
		this->empty = false;
	}


	glm::vec3 getInterpolatedScale(float time, int boneID);

	glm::vec3 getInterpolatedPosition(float time, int boneID);

	aiQuaternion getInterpolatedRotation(float time, int boneID);

};

#endif