#include "Material.h"

RefractiveModel::RefractiveModel(const Ray & ray, const IntersectionRecord & surfaceRecord, const RefractiveMaterial * material)
{
	const glm::vec3& incident = ray.dir;
	glm::vec3 surfaceNormal = surfaceRecord.normal;
	float eta = 1.f / material->GetRefractiveIndex();
	float cosa = -glm::dot(incident, surfaceNormal);
	glm::vec3 fresnel0 = material->GetFresnel0();

	if (cosa < 0.f)
	{
		eta = 1.f / eta;
		surfaceNormal = -surfaceNormal;
		cosa = -cosa;
	}

	float disc = 1.f - (1.f - (cosa * cosa)) * eta * eta;
	if (disc >= 0.0f)
	{
		refractiveCoefficient = glm::vec3(1.f) - (fresnel0 + (glm::vec3(1.f) - fresnel0) * powf(1.f - cosa, 5));
		glm::vec3 refractiveDirection = glm::normalize((incident * eta) + (eta * cosa - sqrtf(disc)) * surfaceNormal);
		refractedRay = Ray(surfaceRecord.intersectionPoint - surfaceNormal * 0.1f, refractiveDirection);
	}

	reflectiveCoefficient = glm::vec3(1.f) - refractiveCoefficient;
	glm::vec3 reflectiveDirection = glm::reflect(incident, surfaceNormal);
	reflectedRay = Ray(surfaceRecord.intersectionPoint + surfaceNormal * 0.1f, reflectiveDirection);
}
