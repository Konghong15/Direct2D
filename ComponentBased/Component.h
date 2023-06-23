#pragma once

#include "eComponentType.h"

namespace componentBased
{
	class Component
	{
	public:
		Component(eComponentType componentType) : mComponentType(componentType) {};
		virtual ~Component() = 0;

		inline eComponentType GetComponentType() const;

	private:
		const eComponentType mComponentType;
	};

	eComponentType Component::GetComponentType() const
	{
		return mComponentType;
	}
}