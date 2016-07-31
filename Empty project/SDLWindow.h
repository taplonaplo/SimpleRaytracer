#pragma once
#include <SDL.h>
#include <stdio.h>

#include "SDLRenderer.h"

class Window
{
public:
	virtual bool HandleEvent() = 0;
	virtual bool IsValid() const = 0;
	virtual void Invalidate() = 0;
};

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
	virtual bool HandleEvent();
};