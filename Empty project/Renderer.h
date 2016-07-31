#pragma once
#include "RenderTarget.h"
#include "Scene.h"
#include "Camera.h"

#include "Material.h"
#include "Ray.h"

class Renderer
{
public:
	virtual void Render() = 0;
};


#define ITERATION_LIMIT 5

class Raytracer : public Renderer
{
protected:
	RenderTarget* renderTarget;
	Scene* scene;
	Camera* camera;

	glm::vec3 TraceRay(const Ray & ray, int iterations);

	glm::vec3 ShadePoint(const IntersectionRecord& record, const Ray& ray, int iterations);
	glm::vec3 ShadeDiffuse(const IntersectionRecord& record);
	glm::vec3 CalculateDirectLighting(const PointLight & light, IntersectionRecord surfceRecord);
	glm::vec3 ShadeReflective(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations);
	glm::vec3 ShadeRefractive(const IntersectionRecord & surfaceRecord, const Ray & ray, int iterations);

public:
	Raytracer(RenderTarget* renderTarget);
	~Raytracer();

	virtual void Render();
};
