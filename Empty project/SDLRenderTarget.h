#pragma once
#include "RenderTarget.h"
#include "SDL.h"

class SDLRenderTarget : public RenderTarget
{
private:
	SDL_Texture* texture;
public:
	SDLRenderTarget(int width, int height, int pixelSize, SDL_Texture* texture)
		: RenderTarget(width, height, pixelSize)
		, texture(texture)
	{ }

	void UploadTexture()
	{
		void* pixels = NULL;
		SDL_LockTexture(texture, NULL, &pixels, &pitch);
		BlitTexture32((uint8_t*)pixels);
		SDL_UnlockTexture(texture);
	}

	void BlitTexture32(uint8_t* pixels)
	{
		for (int i = 0; i < height * width * pixelSize; i += pixelSize)
		{
			pixels[i] = pixelBuffer[i + 3];		// A
			pixels[i + 1] = pixelBuffer[i + 2]; // B
			pixels[i + 2] = pixelBuffer[i + 1];	// G
			pixels[i + 3] = pixelBuffer[i];		// R
		}
	}
};