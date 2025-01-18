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

	glm::vec3 getInterpolatedScale(float time, int boneID)
	{
		float timeInTicks = time * ticksPerSecond;
		if (looped)
		{
			timeInTicks = fmod(timeInTicks, duration);
		}
		if (animationPackets[boneID].s.size() == 1)
		{
			return animationPackets[boneID].s[0].scale;
		}
		else if (animationPackets[boneID].s.size() > 1)
		{
			int id = 0;

			for (int i = 0; i < animationPackets[boneID].s.size() - 1; i++) {
				if (timeInTicks < animationPackets[boneID].s[i + 1].t) {
					id = i;
					break;
				}
			}

			// No interpolation is actually needed when using blender

			glm::vec3 s1 = animationPackets[boneID].s[id].scale;

			return s1;
		}
	}

	glm::vec3 getInterpolatedPosition(float time, int boneID)
	{
		float timeInTicks = time * ticksPerSecond;
		if (looped)
		{
			timeInTicks = fmod(timeInTicks, duration);
		}
		if (animationPackets[boneID].t.size() == 1)
		{
			return animationPackets[boneID].t[0].translation;
		}
		else if (animationPackets[boneID].t.size() > 1)
		{
			int id = 0;
			for (int i = 0; i < animationPackets[boneID].t.size() - 1; i++) {
				if (timeInTicks < animationPackets[boneID].t[i + 1].t) {
					id = i;
					break;
				}
			}

			glm::vec3 s1 = animationPackets[boneID].t[id].translation;

			return s1;
		}
	}

	aiQuaternion getInterpolatedRotation(float time, int boneID)
	{
		float timeInTicks = time * ticksPerSecond;
		if (looped)
		{
			timeInTicks = fmod(timeInTicks, duration);
		}
		if (animationPackets[boneID].r.size() == 1)
		{
			return animationPackets[boneID].r[0].rotation;
		}
		else if (animationPackets[boneID].r.size() > 1)
		{
			int id = 0;
			for (int i = 0; i < animationPackets[boneID].r.size() - 1; i++) {
				if (timeInTicks < animationPackets[boneID].r[i + 1].t) {
					id = i;
					break;
				}
			}

			aiQuaternion Out = animationPackets[boneID].r[id].rotation;

			return Out;
		}
	}

};

#endif