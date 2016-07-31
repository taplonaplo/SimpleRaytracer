#pragma once
#include "glm/glm.hpp"

// to avoid self shadowing
#define MIN_RAY_DIST 0.01f

struct Ray {
	glm::vec3 origin;
	glm::vec3 dir;

	Ray(glm::vec3 origin, glm::vec3 dir)
		: origin(origin)
	{
		this->dir = glm::normalize(dir);
	}
};

struct IntersectionRecord
{
	float distance;
	const Material* material;
	glm::vec3 intersectionPoint;
	glm::vec3 normal;
	IntersectionRecord()
		: distance(FLT_MAX)
		, material(NULL)
	{}
};
