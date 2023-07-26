#include "IRenderable.h"
#include "GameProcessor.h"

namespace d2dFramework
{
	IRenderable::IRenderable()
	{
		GetGameProcessor()->RegisterRenderable(this);
	}

	IRenderable::~IRenderable()
	{
		GetGameProcessor()->UnregisterRenderable(this);
	}
}