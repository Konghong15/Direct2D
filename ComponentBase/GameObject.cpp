#include "GameObject.h"

namespace componentBase
{
	GameObject::GameObject(unsigned long long ID)
		: mID(ID)
	{
		mComponents.reserve(RESERVE_SIZE);
	}

	GameObject::~GameObject()
	{
		for (auto iter = mComponents.begin(); iter != mComponents.end(); ++iter)
		{
			delete (*iter);
		}
	}
}