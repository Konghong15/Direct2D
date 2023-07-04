#pragma once

#include <vector>

namespace componentBase
{
	class Component;

	class GameObject final
	{
	public:
		GameObject(unsigned long long ID);
		~GameObject();

		inline void AddComponent(Component* component);

		inline unsigned long long GetID() const;

	private:
		enum { RESERVE_SIZE = 64 };

		unsigned long long mID;
		std::vector<Component*> mComponents;
	};

	void GameObject::AddComponent(Component* component)
	{
		mComponents.push_back(component);
	}

	unsigned long long GameObject::GetID() const
	{
		return mID;
	}
}