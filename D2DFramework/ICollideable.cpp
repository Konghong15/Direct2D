#include "ICollideable.h"
#include "GameProcessor.h"

namespace d2dFramework
{
	ICollideable::ICollideable()
	{
		GetGameProcessor()->RegisterCollideable(this);
	}

	ICollideable::~ICollideable()
	{
		GetGameProcessor()->UnregisterCollideable(this);
	}
}