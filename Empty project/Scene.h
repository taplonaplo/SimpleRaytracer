#pragma once
#include <vector>
#include "glm/glm.hpp"

#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"

class Scene
{
private:
	std::vector<Sphere> spheres;
	std::vector<PointLight> lights;
	std::vector<Material*> materials;

	void InitializeMaterials();
	void InitializeObjects();
	void InitializeLights();

public:
	Scene();
	IntersectionRecord FindNearestIntersection(const Ray & ray);
	const std::vector<PointLight>& GetLights() const { return lights; }
};
