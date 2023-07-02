#pragma once

#include "eComponentType.h"

namespace entityCamara
{
	class Component
	{
	public:
		Component(unsigned int entityId, eComponentType componentType);
		virtual ~Component() = default;
		Component(const Component& other) = default;
		Component& operator=(const Component& other) = default;
		
		inline unsigned int GetEntityId() const;
		inline eComponentType GetComponentType() const;

	private:
		unsigned int mEntityId;
		const eComponentType mComponentType;
	};

	unsigned int Component::GetEntityId() const
	{
		return mEntityId;
	}

	eComponentType Component::GetComponentType() const
	{
		return mComponentType;
	}
}