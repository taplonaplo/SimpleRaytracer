#pragma once
#include <vector>
#include "glm/glm.hpp"

#define ITERATION_LIMIT 5
#define MIN_RAY_DIST 0.001f

#include <ctime>
struct Ray {
	glm::vec3 origin;
	glm::vec3 dir;

	Ray(glm::vec3 origin, glm::vec3 dir)
		: origin(origin)
	{ 
		this->dir = glm::normalize(dir);
	}
};
struct Material
{
	glm::vec3 diffuse;
	Material(glm::vec3 diffuse)
		: diffuse(diffuse)
	{ }
};

struct IntersectionRecord
{
	float distance;
	const Material* material;
	glm::vec3 intersectionPoint;
	glm::vec3 normal;
	IntersectionRecord()
		: material(NULL)
	{}
};

class Sphere
{
private:
	const Material& material;
	float radius;
	glm::vec3 pos;
public:
	Sphere(float radius, glm::vec3 pos, const Material& material)
		: radius(radius)
		, pos(pos)
		, material(material)
	{ }
	
	
	bool Intersect(const Ray& ray, IntersectionRecord& intersectionRecord)
	{
		// Use the quadratic formula to calculate the distance to the intersection point:
		//	(ray.origin + distance * ray.dir - sphere.center)^2 - sphere.radius^2 = 0;
		glm::vec3 delta = ray.origin - pos;
		float b = glm::dot(ray.dir, delta) * 2.f;
		float c = glm::dot(delta, delta) - radius * radius;
		float d = b * b - 4 * c;

		if (d < 0)
		{
			return false;
		}

		float distance = (-b - sqrtf(d))  * 0.5f;
		if (CheckAndRecordIntersection(intersectionRecord, ray, distance))
		{
			return true;
		}

		distance = (-b + sqrtf(d)) * 0.5f;
		if (CheckAndRecordIntersection(intersectionRecord, ray, distance))
		{
			return true;
		}
		return false;
	}

	bool CheckAndRecordIntersection(IntersectionRecord& intersectionRecord, const Ray& ray, float distance)
	{
		if (distance > MIN_RAY_DIST && distance < intersectionRecord.distance)
		{
			RecordIntersection(intersectionRecord, ray, distance);
			return true;
		}
		return false;
	}

	void RecordIntersection(IntersectionRecord& intersectionRecord, const Ray& ray, float distance)
	{
		intersectionRecord.distance = distance;
		intersectionRecord.intersectionPoint = ray.origin + ray.dir * distance;
		intersectionRecord.normal = GetNormal(intersectionRecord.intersectionPoint);
		intersectionRecord.material = &material;
	}

	glm::vec3 GetNormal(glm::vec3 pos)
	{
		return glm::normalize(pos - this->pos);
	}


};


#define RAND01 (std::rand() / (float)RAND_MAX)
class Scene
{
private:
	std::vector<Sphere> spheres;
	std::vector<Material> materials;
public:
	Scene()
	{
		srand((int32_t)std::time(0));
		for (int i = 0; i < 5; ++i)
		{
			materials.push_back(Material(glm::vec3(RAND01, RAND01, RAND01)));
		}
		for (int i = 0; i < 20; ++i)
		{
			spheres.push_back(Sphere(RAND01 * 50, glm::vec3(RAND01 * 640, 0, RAND01 * 480), materials[rand() % 5]));
		}
	}
	glm::vec3 TraceRay(const Ray& ray, int iterations) {
		if (iterations > ITERATION_LIMIT)
		{
			return glm::vec3(0);
		}

		IntersectionRecord intersectionRecord;
		intersectionRecord.distance = FLT_MAX;
		
		for (size_t i = 0; i < spheres.size(); ++i)
		{
			spheres[i].Intersect(ray, intersectionRecord);
		}
		if (intersectionRecord.material != NULL)
		{
			const Material* material = intersectionRecord.material;
			return 0.5f * intersectionRecord.material->diffuse
				+ 0.5f * intersectionRecord.material->diffuse * glm::dot(intersectionRecord.normal, glm::vec3(0.f, 0.f, 1.f));
		}

		return glm::vec3(0.f, 0.f, 0.f);
	}

};
