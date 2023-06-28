#include <stdarg.h>
#include "Component.h"

namespace entityComponentSystem
{
	Component::Component(unsigned int entityId, eComponentType componentType)
		: mEntityId(entityId)
		, mComponentType(componentType)
	{
	}
}