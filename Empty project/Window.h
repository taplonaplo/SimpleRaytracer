#pragma once
#include "RenderTarget.h"

class Window
{
public:
	virtual const bool IsValid() = 0;
	virtual const void Invalidate() = 0;
	virtual RenderTarget* GetRenderTarget() = 0;
};
