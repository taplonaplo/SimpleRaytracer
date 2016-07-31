#include "stdio.h"
#include "SDLWindow.h"

int main(int argc, char* argv[]) {
	SDLWindow window = SDLWindow("Basic raytracer", 1024, 768);
	if (!window.IsValid())
	{
		return 1;
	}

	bool running = true;
	while (running)
	{
		running = window.HandleEvent();
		window.Invalidate();
	}
	return 0;
}