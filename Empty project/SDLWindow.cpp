#include "SDLWindow.h"


SDLWindow::SDLWindow(const char * title, int width, int height)
	: context(NULL)
	, width(width)
	, height(height)
{
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	}

	window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return;
	}
	
	renderer = new SDLWindowRenderer(window, width, height);

	context = SDL_GL_CreateContext(window);
	
	printf("SDL window created\n");
}

SDLWindow::~SDLWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("SDL window destroyed\n");
}

bool const SDLWindow::IsValid()
{
	return window != NULL;
}

#include "Renderer.h"
void const SDLWindow::Invalidate()
{
	renderer->Invalidate();
}

