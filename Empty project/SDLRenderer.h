#pragma once
#include "SDL.h"
#include "Renderer.h"

class WindowRenderer
{
public:
	virtual void Invalidate() = 0;
};
class SDLWindowRenderer : public WindowRenderer
{
private:
	SDL_Renderer* frameworkRenderer;
	SDL_Texture* frameworkTarget;

	Renderer* sceneRenderer;
	RenderTarget* renderTarget;

	int width;
	int height;
public:
	SDLWindowRenderer(SDL_Window* window, int width, int height)
		: width(width)
		, height(height)	
	{
		frameworkRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		frameworkTarget = SDL_CreateTexture(frameworkRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
		if (frameworkTarget == NULL)
		{
			printf("Could not create texture for window: %s\n", SDL_GetError());
			return;
		}

		renderTarget = new SDLRenderTarget(width, height, 4, frameworkTarget);
		sceneRenderer = new SoftwareRenderer(renderTarget);
	}
	~SDLWindowRenderer()
	{
		delete sceneRenderer;
		delete renderTarget;
		SDL_DestroyTexture(frameworkTarget);
		SDL_DestroyRenderer(frameworkRenderer);
	}

	virtual void Invalidate()
	{
		SDL_SetRenderDrawColor(frameworkRenderer, 0, 0, 0, 255);
		SDL_RenderClear(frameworkRenderer);

		sceneRenderer->Render();
		renderTarget->UploadTexture();

		SDL_RenderCopy(frameworkRenderer, frameworkTarget, NULL, NULL);
		SDL_RenderPresent(frameworkRenderer);
	}

};