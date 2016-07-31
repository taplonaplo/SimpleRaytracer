#include "Sphere.h"

bool Sphere::Intersect(const Ray & ray, IntersectionRecord & intersectionRecord) const
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

Material* Sphere::GetMaterial() const { return material; }

bool Sphere::CheckAndRecordIntersection(IntersectionRecord & intersectionRecord, const Ray & ray, float distance) const
{
	if (distance > MIN_RAY_DIST && distance < intersectionRecord.distance)
	{
		RecordIntersection(intersectionRecord, ray, distance);
		return true;
	}
	return false;
}

void Sphere::RecordIntersection(IntersectionRecord & intersectionRecord, const Ray & ray, float distance) const
{
	intersectionRecord.distance = distance;
	intersectionRecord.intersectionPoint = ray.origin + ray.dir * distance;
	intersectionRecord.normal = GetNormal(intersectionRecord.intersectionPoint);
	intersectionRecord.material = material;
}

glm::vec3 Sphere::GetNormal(glm::vec3 pos) const
{
	return glm::normalize(pos - this->pos);
}
