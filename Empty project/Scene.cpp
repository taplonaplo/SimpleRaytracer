#include "Scene.h"

Scene::Scene()
{
	InitializeMaterials();
	InitializeObjects();
	InitializeLights();
}

void Scene::InitializeMaterials()
{
	materials.push_back(new DiffuseMaterial(glm::vec3(1.f)));
	materials.push_back(new ReflectiveMaterial(glm::vec3(0.9f, 0.9f, 0.9f)));
	materials.push_back(new RefractiveMaterial(glm::vec3(1.5f),glm::vec3(0.f)));

	materials.push_back(new DiffuseMaterial(glm::vec3(0.75f, 0.5f, 0.5f)));
	materials.push_back(new DiffuseMaterial(glm::vec3(0.5f, 0.5f, 0.75f)));
	materials.push_back(new DiffuseMaterial(glm::vec3(0.75f)));
}

void Scene::InitializeObjects()
{
	spheres.push_back(Sphere(60.f, glm::vec3(-60.f, -40.f, -180.f), materials[1]));
	spheres.push_back(Sphere(100.f, glm::vec3(100.f, 0.f, -140.f), materials[2]));

	spheres.push_back(Sphere(100000.f, glm::vec3(-100000.f - 240.f, 0.f, 0.f), materials[3]));
	spheres.push_back(Sphere(100000.f, glm::vec3(+100000.f + 240.f, 0.f, 0.f), materials[4]));
	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, 0.f, -100000.f - 240.f), materials[5]));
	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, 0.f, +100000.f + 240.f), materials[5]));
	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, -100000.f -240.f, 0.f), materials[5]));
}

void Scene::InitializeLights()
{
	lights.push_back(PointLight(glm::vec3(0.f, 0.f, 80.f), glm::vec3(20000.f, 20000.f, 20000.f)));
}

IntersectionRecord Scene::FindNearestIntersection(const Ray & ray)
{
	IntersectionRecord intersectionRecord;
	for (size_t i = 0; i < spheres.size(); ++i)
	{
		spheres[i].Intersect(ray, intersectionRecord);
	}
	return intersectionRecord;
}

