#include "stdio.h"
#include "SDL.h"
#include "SDLWindow.h"
#include "Window.h"
#include "Renderer.h"

#include "glm/glm.hpp"


int main(int argc, char* argv[]) {
	SDLWindow window = SDLWindow("Window class", 640, 480);
	if (!window.IsValid())
	{
		return 1;
	}
	window.Invalidate();
	SDL_Event event;
	bool running = true;
	while (running)
	{
		if (SDL_WaitEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				printf("SDL_QUIT signal received");
				running = false;
			}
		}
		
	}
	return 0;
}