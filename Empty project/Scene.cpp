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
		return ShadePoint(intersectionRecord, ray, iterations);
	}
}

glm::vec3 Scene::ShadePoint(const IntersectionRecord & record, const Ray & ray, int iterations)
{
	const Material& material = *record.material;
	const glm::vec3& normal = record.normal;
	glm::vec3 surfaceColor;

	surfaceColor += ShadeDiffuse(record);
	surfaceColor += ShadeReflective(record, ray, iterations);
	surfaceColor += ShadeRefractive(record, ray, iterations);

	return surfaceColor;
}


glm::vec3 Scene::ShadeDiffuse(const IntersectionRecord & record)
{
	
	if (!record.material->IsDiffuse())
	{
		return glm::vec3();
	}
	else
	{
		glm::vec3 lightContribution;
		for (size_t i = 0; i < lights.size(); ++i)
		{
			lightContribution += CalculateDirectLighting(lights[i], record);
		}

		const glm::vec3& diffuseColor = ((DiffuseMaterial*)record.material)->GetDiffuse();
		glm::vec3 ambientColor = diffuseColor * 0.5f;

		return lightContribution += ambientColor;
	}
}

glm::vec3 Scene::CalculateDirectLighting(const PointLight & light, IntersectionRecord surfceRecord)
{
	const glm::vec3& diffuseColor = ((DiffuseMaterial*)surfceRecord.material)->GetDiffuse();
	const glm::vec3& surfacePoint = surfceRecord.intersectionPoint;
	const glm::vec3& surfaceNormal = surfceRecord.normal;

	glm::vec3 lightDirection = light.GetLightDirection(surfacePoint);
	Ray shadowRay = Ray(surfacePoint + surfaceNormal * 0.1f, lightDirection);

	IntersectionRecord shadowRecord = FindNearestIntersection(shadowRay);
	float lightDistance = light.GetDistance(surfacePoint);
	if (shadowRecord.distance > lightDistance)
	{
		float weight = glm::clamp(dot(surfaceNormal, lightDirection), 0.f, 1.f);
		glm::vec3 power = light.GetPower(lightDistance);
		return weight * power;
	}
	return glm::vec3();
}


glm::vec3 Scene::ShadeReflective(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations)
{
	if (!surfaceRecord.material->IsReflective())
	{
		return glm::vec3();
	}
	else
	{
 		const ReflectiveMaterial* material = ((ReflectiveMaterial*)surfaceRecord.material);
		const glm::vec3& reflectiveColor = material->GetReflective();

		const glm::vec3 reflectionDirection = material->GetReflectionDirection(ray.dir, surfaceRecord.normal);
		const Ray reflectedRay = Ray(surfaceRecord.intersectionPoint + surfaceRecord.normal * 0.1f, reflectionDirection);
		const glm::vec3 reflectedColor = TraceRay(reflectedRay, iterations + 1);

		return reflectiveColor * reflectedColor;
	}
}

glm::vec3 Scene::ShadeRefractive(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations)
{
	if (!surfaceRecord.material->IsRefractive())
	{
		return glm::vec3();
	}
	else
	{
		glm::vec3 lightContribution;
		RefractiveModel model = ((RefractiveMaterial*)surfaceRecord.material)->GetRefractiveModel(ray, surfaceRecord);
		if (model.HasReflection())
		{
			Ray reflectedRay = model.GetReflectedRay();
			glm::vec3 reflectiveCoefficient = model.GetReflectiveCoefficient();
			lightContribution += reflectiveCoefficient * TraceRay(reflectedRay, iterations + 1);
		}
		if (model.HasRefraction())
		{
			Ray refractedRay = model.GetRefractedRay();
			glm::vec3 refractiveCoefficient = model.GetRefractiveCoefficient();
			lightContribution += refractiveCoefficient * TraceRay(refractedRay, iterations + 1);
		}
		return lightContribution;
	}
}