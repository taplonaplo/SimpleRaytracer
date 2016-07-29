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

	SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window, &renderer);

	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return;
	}
	
	target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (target == NULL)
	{
		printf("Could not create texture for window: %s\n", SDL_GetError());
		return;
	}
	renderTarget = new SDLRenderTarget(width, height, 4, target);

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

RenderTarget* SDLWindow::GetRenderTarget()
{
	return renderTarget;
}

bool const SDLWindow::IsValid()
{
	return window != NULL && renderer != NULL;
}

#include "Renderer.h"
void const SDLWindow::Invalidate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	Renderer renderer2 = Renderer(renderTarget);
	renderer2.Render();
	renderTarget->UploadTexture();

	SDL_RenderCopy(renderer, target, NULL, NULL);
	SDL_RenderPresent(renderer);
}

