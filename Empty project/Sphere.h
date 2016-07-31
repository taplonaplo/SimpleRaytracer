#pragma once
#include "glm/glm.hpp"
#include "Material.h"
#include "Ray.h"

class Sphere
{
private:
	Material* material;
	float radius;
	glm::vec3 pos;

	bool CheckAndRecordIntersection(IntersectionRecord& intersectionRecord, const Ray& ray, float distance) const;
	void RecordIntersection(IntersectionRecord& intersectionRecord, const Ray& ray, float distance) const;
public:
	Sphere(float radius, glm::vec3 pos, Material* material)
		: radius(radius)
		, pos(pos)
		, material(material)
	{ }

	// Calculate up to 2 intersection points with the sphere, and return the closer one if it exists.
	bool Intersect(const Ray& ray, IntersectionRecord& intersectionRecord) const;
	Material* GetMaterial() const;
	glm::vec3 GetNormal(glm::vec3 pos) const;
};