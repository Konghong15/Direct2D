#include "IFixedUpdateable.h"
#include "GameProcessor.h"

namespace d2dFramework
{
	IFixedUpdateable::IFixedUpdateable()
	{
		GetGameProcessor()->RegisterFixedUpdateable(this);
	}

	IFixedUpdateable::~IFixedUpdateable()
	{
		GetGameProcessor()->UnregisterFixedUpdateable(this);
	}
}