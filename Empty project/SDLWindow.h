#pragma once
#include "Window.h"
#include <SDL.h>
#include <stdio.h>

// TODO move to SDL renderer
#include "SDLRenderTarget.h"
#include "SDLRenderer.h"

// SDLWindow with OpenGL
class SDLWindow : public Window {
private:
	SDL_Window* window;
	WindowRenderer* renderer;
	SDL_Texture* target;
	SDL_GLContext context;
	
	int width;
	int height;
public:
	SDLWindow(const char* title, int width, int height);
	~SDLWindow();
	virtual bool const IsValid();
	virtual void const Invalidate();
	
};