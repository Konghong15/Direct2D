#include <stdarg.h>
#include "Component.h"

namespace entityCamara
{
	Component::Component(unsigned int entityId, eComponentType componentType)
		: mEntityId(entityId)
		, mComponentType(componentType)
	{
	}
}