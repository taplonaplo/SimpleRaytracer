#pragma once
#include "Window.h"
#include <SDL.h>
#include <stdio.h>

#include "SDLRenderer.h"

// SDLWindow with OpenGL
class SDLWindow : public Window {
private:
	SDL_Window* window;
	WindowRenderer* renderer;
	SDL_GLContext context;
	
	int width;
	int height;
public:
	SDLWindow(const char* title, int width, int height);
	~SDLWindow();
	virtual bool IsValid() const;
	virtual void Invalidate();
	
};