#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "SDLRenderTarget.h"

class WindowRenderer
{
public:
	virtual void Invalidate() = 0;
};
class SDLWindowRenderer : public WindowRenderer
{
private:
	SDL_Renderer* windowRenderer;
	SDL_Texture* windowTarget;

	Renderer* sceneRenderer;
	RenderTarget* renderTarget;

	int width;
	int height;
public:
	SDLWindowRenderer(SDL_Window* window, int width, int height)
		: width(width)
		, height(height)	
	{
		windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		windowTarget = SDL_CreateTexture(windowRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		if (windowTarget == NULL)
		{
			printf("Could not create texture for window: %s\n", SDL_GetError());
			return;
		}

		renderTarget = new SDLRenderTarget(width, height, 4, windowTarget);
		sceneRenderer = new Raytracer(renderTarget);
	}

	~SDLWindowRenderer()
	{
		delete sceneRenderer;
		delete renderTarget;
		SDL_DestroyTexture(windowTarget);
		SDL_DestroyRenderer(windowRenderer);
	}

	virtual void Invalidate()
	{
		SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 255);
		SDL_RenderClear(windowRenderer);

		sceneRenderer->Render();
		renderTarget->UploadTexture();

		SDL_RenderCopy(windowRenderer, windowTarget, NULL, NULL);
		SDL_RenderPresent(windowRenderer);
	}
};