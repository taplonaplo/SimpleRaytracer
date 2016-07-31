#pragma once
#include "RenderTarget.h"

class Window
{
public:
	virtual bool IsValid() const = 0;
	virtual void Invalidate() = 0;
};
