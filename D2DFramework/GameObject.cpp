#include "GameObject.h"
#include "Component.h"

namespace d2dFramework
{
	GameObject::GameObject(unsigned int id)
		: BaseEntity(id)
	{
	}

	GameObject::~GameObject()
	{
		for (auto pair : mComponents)
		{
			delete pair.second;
		}
	}

	void GameObject::Init()
	{
		for (auto keyComponent : mComponents)
		{
			Component* component = keyComponent.second;
			component->Init();
		}
	}

	void GameObject::Release()
	{
		for (auto keyComponent : mComponents)
		{
			keyComponent.second->Release();
		}
	}
}