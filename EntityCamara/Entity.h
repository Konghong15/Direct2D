#pragma once

#include <cassert>

#include "eComponentType.h"
#include "Component.h"

namespace entityCamara
{
	class Component;

	class Entity
	{
	public:
		Entity(unsigned int id);
		virtual ~Entity();
		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity& other) = delete;

		bool CheckBitflag(unsigned int count, eComponentType  ...) const;

		inline void AddComponent(Component* component);
		inline void RemoveComponent(eComponentType componentType);

		inline unsigned int GetEntityId() const;
		inline unsigned long long GetComponentflag() const;
		inline Component* GetComponentOrNull(eComponentType componentType);

	private:
		unsigned int mID;
		unsigned long long mComponentflag;
		Component* mComponents[static_cast<unsigned int>(eComponentType::Size)];
	};

	void Entity::AddComponent(Component* component)
	{
		unsigned int index = static_cast<unsigned int>(component->GetComponentType());
		mComponents[index] = component;

		// bool vector 추가 예정
		assert(index < 64u);
		mComponentflag |= 1llu << index;
	}

	void Entity::RemoveComponent(eComponentType componentType)
	{
		unsigned int index = static_cast<unsigned int>(componentType);
		delete mComponents[index];
		mComponents[index] = nullptr;

		// bool vector 추가 예정
		assert(index < 64u);
		mComponentflag ^= ~(1llu << index);
	}

	unsigned int Entity::GetEntityId() const
	{
		return mID;
	}

	unsigned long long Entity::GetComponentflag() const
	{
		return mComponentflag;
	}

	Component* Entity::GetComponentOrNull(eComponentType componentType)
	{
		unsigned int index = static_cast<unsigned int>(componentType);

		return mComponents[index];
	}
}