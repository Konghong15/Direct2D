#include "ObjectManager.h"

namespace d2dFramework
{
	ObjectManager::ObjectManager()
	{
		mObjectMap.reserve(RESERVE_SIZE);
	}

	ObjectManager::~ObjectManager()
	{
		for (auto iter = mObjectMap.begin(); iter != mObjectMap.end(); ++iter)
		{
			GameObject* gameObject = iter->second;

			delete gameObject;
		}

		mObjectMap.clear();
	}
}