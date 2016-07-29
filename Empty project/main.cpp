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

	getchar();
	return 0;
}