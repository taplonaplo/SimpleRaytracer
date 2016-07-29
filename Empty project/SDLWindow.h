#pragma once
#include "Window.h"
#include <SDL.h>
#include <stdio.h>

// TODO move to SDL renderer
#include "SDLRenderTarget.h"

// SDLWindow with OpenGL
class SDLWindow : public Window {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* target;
	SDL_GLContext context;
	RenderTarget* renderTarget;
	
	int width;
	int height;
public:
	SDLWindow(const char* title, int width, int height);
	~SDLWindow();
	virtual RenderTarget* GetRenderTarget();
	virtual bool const IsValid();
	virtual void const Invalidate();
	
};