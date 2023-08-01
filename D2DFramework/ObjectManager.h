#pragma once

#include <cassert>
#include <unordered_map>
#include <queue>

#include "GameObject.h"

namespace d2dFramework
{
	class ObjectManager
	{
		friend class GameProcessor;

	public:
		static ObjectManager* GetInstance();

		inline GameObject* CreateObject(unsigned int id);
		inline GameObject* FindObjectOrNull(unsigned int id);
		inline void DeletObject(unsigned int id);

	private:
		ObjectManager();
		~ObjectManager();
		ObjectManager(const ObjectManager&) = delete;
		ObjectManager& operator=(const ObjectManager&) = delete;

		void handleDeleteObject();
		void release();

	private:
		enum { RESERVE_SIZE = 4096 };

		static ObjectManager* mInstance;

		std::unordered_map<unsigned int, GameObject*> mValidObjectMap;
		std::queue<unsigned int> mDeleteObject;
	};

	GameObject* ObjectManager::CreateObject(unsigned int id)
	{
		auto iter = mValidObjectMap.find(id);
		assert(iter == mValidObjectMap.end());

		return new GameObject(id);
	}

	GameObject* ObjectManager::FindObjectOrNull(unsigned int id)
	{
		auto iter = mValidObjectMap.find(id);
		if (iter == mValidObjectMap.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	void ObjectManager::DeletObject(unsigned int id)
	{
		mDeleteObject.push(id);
	}
}