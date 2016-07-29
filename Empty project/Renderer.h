#pragma once
#include "RenderTarget.h"
#include "Scene.h"

class Renderer
{
private:
	RenderTarget* renderTarget;
	Scene* scene;
public:
	Renderer(RenderTarget* renderTarget) : renderTarget(renderTarget) { }
	void Render()
	{
		int width = renderTarget->getWidth();
		int height = renderTarget->getHeight();

		scene = new Scene();
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				glm::vec3 color;
				IntersectionRecord record;
				record.distance = FLT_MAX;
				Ray ray = Ray(glm::vec3(i, 500.f, j), glm::vec3(0.f, -1.f, 0.f));
				color = scene->TraceRay(ray, 5);

				renderTarget->storePixel(i, j, glm::vec4(color.r, color.g, color.b, 1.0f));
			}
		}
	}
};
