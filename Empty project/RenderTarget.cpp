#include "RenderTarget.h"

RenderTarget::RenderTarget(int width, int height, int pixelSize)
	: pixelBuffer(NULL)
	, width(width)
	, height(height)
	, pixelSize(pixelSize)
	, pitch(width * pixelSize)
{
	pixelBuffer = (new uint8_t[width * height * pixelSize]);
}

RenderTarget::~RenderTarget()
{
	delete[] pixelBuffer;
}

void RenderTarget::storePixel(int x, int y, glm::vec4 color)
{
	int offset = ((height - 1) - y) * width * pixelSize + x * pixelSize;
	glm::vec4 clampedColor = glm::clamp(color, glm::vec4(0.f), glm::vec4(0.999f));
	clampedColor *= 256;
	pixelBuffer[offset] = (uint8_t)clampedColor.r;
	pixelBuffer[offset + 1] = (uint8_t)clampedColor.g;
	pixelBuffer[offset + 2] = (uint8_t)clampedColor.b;
	pixelBuffer[offset + 3] = (uint8_t)clampedColor.a;
}
