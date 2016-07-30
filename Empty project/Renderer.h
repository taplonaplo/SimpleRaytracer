#pragma once
#include "RenderTarget.h"
#include "Scene.h"

class Renderer
{
public:
	virtual void Render() = 0;
};

class SoftwareRenderer : public Renderer
{
protected:
	RenderTarget* renderTarget;
	Scene* scene;
public:
	SoftwareRenderer(RenderTarget* renderTarget)
		: renderTarget(renderTarget)
	{ 
		scene = new Scene();
	}

	virtual void Render()
	{
		int width = renderTarget->getWidth();
		int height = renderTarget->getHeight();
	
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				Ray ray = Ray(glm::vec3(i, 500.f, j), glm::vec3(0.f, -1.f, 0.f));
				glm::vec3 color = scene->TraceRay(ray, 5);

				renderTarget->storePixel(i, j, glm::vec4(color.r, color.g, color.b, 1.0f));
			}
		}
	}
};
