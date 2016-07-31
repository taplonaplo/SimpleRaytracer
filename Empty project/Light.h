#pragma once
#include "glm/glm.hpp"

class PointLight
{
private:
	glm::vec3 position;
	glm::vec3 power;
public:
	PointLight(glm::vec3 position, glm::vec3 power)
		: position(position)
		, power(power)
	{ }

	float GetDistance(glm::vec3 surfacePoint) const { return glm::length(surfacePoint - position); }
	glm::vec3 GetPosition() const { return position; }
	glm::vec3 GetLightDirection(glm::vec3 surfacePoint) const { return glm::normalize(position - surfacePoint); }
	glm::vec3 GetPower(float distance) const { return power / (distance * distance); }
};
