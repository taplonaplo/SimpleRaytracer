#pragma once
#include "glm/glm.hpp"

class RenderTarget
{
protected:
	uint8_t* pixelBuffer;
	int width;
	int height;
	int pixelSize;
	int pitch;
public:
	RenderTarget(int width, int height, int pixelSize);
	~RenderTarget();

	uint8_t* getPixelBuffer() { return pixelBuffer; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getPixelSize() const { return pixelSize; }
	int getPitch() const { return pitch; }

	void storePixel(int x, int y, glm::vec4 color);
	virtual void UploadTexture() = 0;
};