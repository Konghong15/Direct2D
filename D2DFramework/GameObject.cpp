#include "GameObject.h"

namespace d2dFramework
{
	GameObject::GameObject(unsigned int id)
		: mId(id)
	{
	}

	GameObject::~GameObject()
	{
		for (auto pair : mComponents)
		{
			delete pair.second;
		}
	}
}