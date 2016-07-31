#pragma once
#include "RenderTarget.h"
#include "SDL.h"

class SDLRenderTarget : public RenderTarget
{
private:
	SDL_Texture* texture;
	void BlitTexture32(uint8_t* pixels);
public:
	SDLRenderTarget(int width, int height, int pixelSize, SDL_Texture* texture)
		: RenderTarget(width, height, pixelSize)
		, texture(texture)
	{ }

	void UploadTexture();
	
};