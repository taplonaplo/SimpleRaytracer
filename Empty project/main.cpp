#include "stdio.h"
#include "SDL.h"
#include "SDLWindow.h"

int main(int argc, char* argv[]) {
	SDLWindow window =SDLWindow("Window class",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480
	);
	getchar();
	return 0;
}