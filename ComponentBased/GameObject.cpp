#include "GameObject.h"
#include "Component.h"

namespace componentBased
{
	GameObject::GameObject(const std::string name)
		: mName(name)
	{
		mComponents.reserve(RESERVE_SIZE);
	}

	GameObject::~GameObject()
	{
		for (auto iter = mComponents.begin(); iter != mComponents.end(); ++iter)
		{
			delete (*iter);
		}

		mComponents.clear();
	}

	void GameObject::AddComponent(Component* component)
	{
		mComponents.push_back(component);
	}

	void GameObject::Update()
	{
		for (auto iter = mComponents.begin(); iter != mComponents.end(); ++iter)
		{
			iter->Up
		}
	}
}