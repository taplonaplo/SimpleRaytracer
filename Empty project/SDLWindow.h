#pragma once
#include <SDL.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

class SDLWindow {
private:
	SDL_Window* window;
	SDL_GLContext context;
public:
	SDLWindow(const char* title, int posX, int posY, int sizeX, int sizeY);
	~SDLWindow();
};