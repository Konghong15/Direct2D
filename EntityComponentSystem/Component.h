#pragma once

#include "eComponentType.h"

namespace entityComponentSystem
{
	struct Component
	{
		Component(eComponentType componentType) : mComponentType(componentType) {};
		virtual ~Component() = 0;

		const eComponentType mComponentType;
		// entity id
	};
}