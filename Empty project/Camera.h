#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "Ray.h"
#include "math.h"

class Camera
{
public:
	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;
	glm::vec3 right;
	float fieldOfView;
public:
	Camera(glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, glm::vec3 right, float fieldOfView)
		: eye(eye)
		, lookAt(lookAt)
		, up(up)
		, right(right)
		, fieldOfView(fieldOfView)
	{
	}
	Ray GetRay(int x, int y, int width, int height)
	{
		float aspectRatio = width > height ? width / (float)height : height / (float)width;
		float yOffset = 2.f * (y - height / 2) * tanf(fieldOfView / 2.f * glm::pi<float>() / 180.f);
		float xOffset = 2.f * (x - width / 2)  * tanf(fieldOfView / 2.f * glm::pi<float>() / 180.f);
		glm::vec3 target = (lookAt + up * yOffset + right * xOffset) - eye;
		return Ray(eye, glm::normalize(target));
	}
};
