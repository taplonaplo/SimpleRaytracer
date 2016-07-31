#pragma once
#include "glm/glm.hpp"

class RenderTarget
{
protected:
	unsigned char* pixelBuffer;
	int width;
	int height;
	int pixelSize;
	int pitch;
public:
	RenderTarget(int width, int height, int pixelSize)
		: pixelBuffer(NULL)
		, width(width)
		, height(height)
		, pixelSize(pixelSize)
		, pitch(width * pixelSize)
	{
		pixelBuffer = (new unsigned char[width * height * pixelSize]);
	}
	~RenderTarget()
	{
		delete[] pixelBuffer;
	}
	unsigned char* getPixelBuffer() { return pixelBuffer; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getPixelSize() const { return pixelSize; }
	int getPitch() const { return pitch; }
	
	void storePixel(int x, int y, glm::vec4 color)
	{
		int offset = (height - y) * width * pixelSize + x * pixelSize;
		glm::vec4 clampedColor = glm::clamp(color, glm::vec4(0.f), glm::vec4(0.999f));
		clampedColor *= 256;
		pixelBuffer[offset] = (uint8_t)clampedColor.r;
		pixelBuffer[offset + 1] = (uint8_t)clampedColor.g;
		pixelBuffer[offset + 2] = (uint8_t)clampedColor.b;
		pixelBuffer[offset + 3] = (uint8_t)clampedColor.a;
	}
	virtual void UploadTexture() { }
};