#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Ray.h"
class Camera
{
public:
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
	Ray GetRay(int x, int y, int width, int height)
	{
		float yOffset = 2.f * (y - height / 2);
		float xOffset = 2.f * (x - width / 2);
		glm::vec3 target = (lookAt + up * yOffset + right * xOffset) - eye;
		return Ray(eye, glm::normalize(target));
	}
};
