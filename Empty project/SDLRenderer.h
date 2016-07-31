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
	SDLWindowRenderer(SDL_Window* window, int width, int height);

	~SDLWindowRenderer();

	virtual void Invalidate();
};