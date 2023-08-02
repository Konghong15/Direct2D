#include "ObjectManager.h"

#include "eFrameworkID.h"

namespace d2dFramework
{
	ObjectManager* ObjectManager::mInstance = nullptr;

	ObjectManager* ObjectManager::GetInstance()
	{
		assert(mInstance != nullptr);
		return mInstance;
	}

	ObjectManager::ObjectManager()
		: BaseEntity(static_cast<unsigned int>(eFramworkID::ObjectManager))
	{
		mValidObjectMap.reserve(RESERVE_SIZE);
	}

	ObjectManager::~ObjectManager()
	{
		release();
	}

	void ObjectManager::handleDeleteObject()
	{
		while (!mDeleteObject.empty())
		{
			auto iter = mValidObjectMap.find(mDeleteObject.front());

			if (iter != mValidObjectMap.end())
			{
				delete iter->second;
				mValidObjectMap.erase(iter);
			}
		}
	}

	void ObjectManager::release()
	{
		for (auto iter = mValidObjectMap.begin(); iter != mValidObjectMap.end(); ++iter)
		{
			GameObject* gameObject = iter->second;

			delete gameObject;
		}

		mValidObjectMap.clear();
	}
}