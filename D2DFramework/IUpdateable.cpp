#include "IUpdateable.h"
#include "GameProcessor.h"

namespace d2dFramework
{
	IUpdateable::IUpdateable()
	{
		GetGameProcessor()->RegisterUpdateable(this);
	}

	IUpdateable::~IUpdateable()
	{
		GetGameProcessor()->UnregisterUpdateable(this);
	}
}