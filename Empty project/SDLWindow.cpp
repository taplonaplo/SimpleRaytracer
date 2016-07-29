#include "SDLWindow.h"

SDLWindow::SDLWindow(const char * title, int posX, int posY, int sizeX, int sizeY) : context(NULL)
{
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

	window = SDL_CreateWindow(title, posX, posY, sizeX, sizeY, SDL_WINDOW_OPENGL);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return;
	}

	printf("SDL window created\n");
	context = SDL_GL_CreateContext(window);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

SDLWindow::~SDLWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("SDL window destroyed\n");
}
