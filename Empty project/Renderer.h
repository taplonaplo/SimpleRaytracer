#pragma once
#include "RenderTarget.h"
#include "Scene.h"
#include "Camera.h"

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
	Camera* camera;
public:
	SoftwareRenderer(RenderTarget* renderTarget)
		: renderTarget(renderTarget)
	{ 
		scene = new Scene();
		camera = new Camera(
			glm::vec3(0.f, 500.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(1.f, 0.f, 0.f)
		);
	}
	SoftwareRenderer()
	{
		delete scene;
	}

	virtual void Render()
	{
		int width = renderTarget->getWidth();
		int height = renderTarget->getHeight();
	
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				Ray ray = camera->GetRay(i, j, width, height);
				glm::vec3 color = scene->TraceRay(ray, 5);

				renderTarget->storePixel(i, j, glm::vec4(color.r, color.g, color.b, 1.0f));
			}
		}
	}
};
