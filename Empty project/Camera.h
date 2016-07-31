#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
class Camera
{
private:
	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;
	glm::vec3 right;
public:
	Camera(glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, glm::vec3 right)
		: eye(eye)
		, lookAt(lookAt)
		, up(up)
		, right(right)
	{ }
	Ray GetRay()
	{
		//glm::mat4 lookAt = glm::lookAt();
	}
};
