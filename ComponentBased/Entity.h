#pragma once

#include <cassert>

#include "eComponentType.h"
#include "Component.h"

namespace componentBased
{
	class Component;

	class Entity
	{
		Entity() : mComponentflag(0u), mComponents{ 0, } {};
		~Entity() { for (int i = 0; i < static_cast<unsigned int>(eComponentType::Size); ++i) { delete mComponents[i]; } };
		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity& other) = delete;

		inline void AddComponent(Component* component);
		inline void RemoveComponent(eComponentType componentType);
		inline Component* GetComponentOrNull(eComponentType componentType);

	private:
		unsigned long long mComponentflag;
		Component* mComponents[static_cast<unsigned int>(eComponentType::Size)];
	};

	void Entity::AddComponent(Component* component)
	{
		unsigned int index = static_cast<unsigned int>(component->GetComponentType());
		mComponents[index] = component;

		// bool vector 추가 예정
		assert(index < 64u);
		mComponentflag |= 1 << index;
	}

	void Entity::RemoveComponent(eComponentType componentType)
	{
		unsigned int index = static_cast<unsigned int>(componentType);
		mComponents[index] = nullptr;

		// bool vector 추가 예정
		assert(index < 64u);
		mComponentflag ^= ~(1 << index);
	}

	Component* Entity::GetComponentOrNull(eComponentType componentType)
	{
		unsigned int index = static_cast<unsigned int>(componentType);

		return mComponents[index];
	}
}