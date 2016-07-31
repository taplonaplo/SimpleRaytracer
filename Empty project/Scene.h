#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"

#include <ctime>

#define ITERATION_LIMIT 5
#define RAND01 (std::rand() / (float)RAND_MAX)

class Scene
{
private:
	std::vector<Sphere> spheres;
	std::vector<PointLight> lights;
	std::vector<Material*> materials;


	void InitializeMaterials();
	void InitializeObjects();
	void InitializeLights();

	IntersectionRecord FindNearestIntersection(const Ray & ray);
	glm::vec3 ShadePoint(const IntersectionRecord& record, const Ray& ray);
	glm::vec3 ShadeDiffuse(const IntersectionRecord& record, const Ray& ray);
public:
	Scene();

	glm::vec3 TraceRay(const Ray& ray, int iterations);
};
