#include "Scene.h"

Scene::Scene()
{
	srand((int32_t)std::time(0));

	InitializeMaterials();
	InitializeObjects();
	InitializeLights();
}

void Scene::InitializeMaterials()
{
	materials.push_back(new DiffuseMaterial(glm::vec3(1.f)));
	for (int i = 0; i < 20; ++i)
	{
		materials.push_back(new DiffuseMaterial(glm::vec3(RAND01, RAND01, RAND01)));
	}
}

void Scene::InitializeObjects()
{
	spheres.push_back(Sphere(60.f, glm::vec3(-60.f, -40.f, -180.f), materials[1]));
	spheres.push_back(Sphere(100.f, glm::vec3(150.f, -100.f, -140.f), materials[1]));

	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, 0.f, -100000.f - 240.f), materials[2]));
	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, 0.f, +100000.f + 240.f), materials[3]));
	spheres.push_back(Sphere(100000.f, glm::vec3(-100000.f - 240.f, 0.f, 0.f), materials[4]));
	spheres.push_back(Sphere(100000.f, glm::vec3(+100000.f + 240.f, 0.f, 0.f), materials[5]));
	spheres.push_back(Sphere(100000.f, glm::vec3(0.f, -100000.f -240.f, 0.f), materials[6]));
	/*for (int i = 0; i < 20; ++i)
	{
		spheres.push_back(Sphere(RAND01 * 10.f + 25.f, glm::vec3(RAND01 * 640, 0, RAND01 * 480), materials[i + 1]));
	}*/
}

void Scene::InitializeLights()
{
	lights.push_back(PointLight(glm::vec3(0.f, 0.f, 80.f), glm::vec3(10000.f, 10000.f, 10000.f)));
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

glm::vec3 Scene::TraceRay(const Ray & ray, int iterations) {
	if (iterations > ITERATION_LIMIT)
	{
		return glm::vec3(0);
	}

	IntersectionRecord intersectionRecord = FindNearestIntersection(ray);
	if (intersectionRecord.material == NULL)
	{
		return glm::vec3(0.f, 0.f, 0.f);
	}
	else
	{
		return ShadePoint(intersectionRecord, ray);
	}
}

glm::vec3 Scene::ShadePoint(const IntersectionRecord & record, const Ray & ray)
{
	const Material& material = *record.material;
	const glm::vec3& normal = record.normal;
	glm::vec3 surfaceColor;

	surfaceColor += ShadeDiffuse(record, ray);
	return surfaceColor;
}


glm::vec3 Scene::ShadeDiffuse(const IntersectionRecord & record, const Ray & ray)
{
	glm::vec3 lightContribution;
	if (!record.material->IsDiffuse())
	{
		return lightContribution;
	}
	else
	{
		const glm::vec3& diffuseColor = ((DiffuseMaterial*)record.material)->GetDiffuse();
		const glm::vec3& surfacePoint = record.intersectionPoint;
		const glm::vec3& surfaceNormal = record.normal;

		for (int i = 0; i < lights.size(); ++i)
		{
			const PointLight& light = lights[i];
			glm::vec3 lightDirection = light.GetLightDirection(surfacePoint);
			Ray shadowRay = Ray(surfacePoint + surfaceNormal * 0.1f, lightDirection);

			IntersectionRecord shadowRecord = FindNearestIntersection(shadowRay);
			float lightDistance = light.GetDistance(surfacePoint);
			if (shadowRecord.distance > lightDistance )
			{
				float weight = glm::clamp(dot(surfaceNormal, lightDirection), 0.f, 1.f);
				glm::vec3 power = light.GetPower(lightDistance);
				lightContribution += diffuseColor * weight * power;
			}
		}

		glm::vec3 ambientColor = diffuseColor * 0.5f;
		lightContribution += ambientColor;
		
	}
	return lightContribution;
}

