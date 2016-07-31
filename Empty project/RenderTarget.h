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
	
	void storePixel(int x, int y, glm::vec4 color);
	virtual void UploadTexture() = 0;
};