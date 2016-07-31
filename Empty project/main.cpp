#include "stdio.h"
#include "SDLWindow.h"

int main(int argc, char* argv[]) {
	SDLWindow window = SDLWindow("Window class", 1024, 768);
	if (!window.IsValid())
	{
		return 1;
	}
	
	bool running = true;
	while (running)
	{
		window.Invalidate();
	}
	return 0;
}