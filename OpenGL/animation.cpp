#include "animation.h"

#include <iostream>

glm::vec3 Animation::getInterpolatedScale(float time, int boneID)
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

glm::vec3 Animation::getInterpolatedPosition(float time, int boneID)
{
	float timeInTicks = time * ticksPerSecond;
	if (looped)
	{
		timeInTicks = fmod(timeInTicks, duration);
	}
	if (animationPackets[boneID].t.size() ==1)
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

aiQuaternion Animation::getInterpolatedRotation(float time, int boneID)
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