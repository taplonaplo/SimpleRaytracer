#include "Renderer.h"

Raytracer::Raytracer(RenderTarget * renderTarget)
	: renderTarget(renderTarget)
{
	scene = new Scene();
	camera = new Camera(
		glm::vec3(0.f, 500.f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(1.f, 0.f, 0.f),
		60.f
	);
}

Raytracer::~Raytracer()
{
	delete scene;
	delete camera;
}

void Raytracer::Render()
{
	int width = renderTarget->getWidth();
	int height = renderTarget->getHeight();

	#pragma omp parallel for num_threads(4) 
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Ray ray = camera->GetRay(i, j, width, height);
			glm::vec3 color = TraceRay(ray, 0);

			renderTarget->storePixel(i, j, glm::vec4(color.r, color.g, color.b, 1.0f));
		}
	}
}

glm::vec3 Raytracer::TraceRay(const Ray & ray, int iterations) {
	if (iterations > ITERATION_LIMIT)
	{
		return glm::vec3(0);
	}

	IntersectionRecord intersectionRecord = scene->FindNearestIntersection(ray);
	if (intersectionRecord.material == NULL)
	{
		return glm::vec3(0.f, 0.f, 0.f);
	}
	else
	{
		return ShadePoint(intersectionRecord, ray, iterations);
	}
}

glm::vec3 Raytracer::ShadePoint(const IntersectionRecord & record, const Ray & ray, int iterations)
{
	const Material& material = *record.material;
	const glm::vec3& normal = record.normal;
	glm::vec3 surfaceColor;

	surfaceColor += ShadeDiffuse(record);
	surfaceColor += ShadeReflective(record, ray, iterations);
	surfaceColor += ShadeRefractive(record, ray, iterations);

	return surfaceColor;
}


glm::vec3 Raytracer::ShadeDiffuse(const IntersectionRecord & record)
{

	if (!record.material->IsDiffuse())
	{
		return glm::vec3();
	}
	else
	{
		glm::vec3 lightContribution;
		const std::vector<PointLight>& lights = scene->GetLights();
		for (size_t i = 0; i < lights.size(); ++i)
		{
			lightContribution += CalculateDirectLighting(lights[i], record);
		}

		const glm::vec3& diffuseColor = ((DiffuseMaterial*)record.material)->GetDiffuse();
		glm::vec3 ambientColor = diffuseColor * 0.5f;

		return lightContribution += ambientColor;
	}
}

glm::vec3 Raytracer::CalculateDirectLighting(const PointLight & light, IntersectionRecord surfceRecord)
{
	const glm::vec3& diffuseColor = ((DiffuseMaterial*)surfceRecord.material)->GetDiffuse();
	const glm::vec3& surfacePoint = surfceRecord.intersectionPoint;
	const glm::vec3& surfaceNormal = surfceRecord.normal;

	glm::vec3 lightDirection = light.GetLightDirection(surfacePoint);
	Ray shadowRay = Ray(surfacePoint + surfaceNormal * 0.1f, lightDirection);

	IntersectionRecord shadowRecord = scene->FindNearestIntersection(shadowRay);
	float lightDistance = light.GetDistance(surfacePoint);
	if (shadowRecord.distance > lightDistance)
	{
		float weight = glm::clamp(dot(surfaceNormal, lightDirection), 0.f, 1.f);
		glm::vec3 power = light.GetPower(lightDistance);
		return weight * power;
	}
	return glm::vec3();
}


glm::vec3 Raytracer::ShadeReflective(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations)
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

glm::vec3 Raytracer::ShadeRefractive(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations)
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